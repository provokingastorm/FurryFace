// TetrisGameSession.cpp
#include "cheezepizzaengine.h"
#include "hgeresource.h"
#include "tetrisgamesession.h"
#include "tetrishud.h"
#include "tetrisblock.h"
#include "block.h"
#include "tetrisgrid.h"
#include "tetrisblockfactory.h"
#include "vector2d.h"
#include "debugutilities.h"

/*****MISC DATA******
    screenX = 240;
    screenY = 91;
    screenHeight = 339;
    screenWidth = 169;
 ********************/

/** The base values whenever the player lands a Tetris Block in the grid */
#define BLOCK_LANDED_POINTS 5

#define TETRIS_BLOCK_SECTION "TetrisBlock"

namespace
{
	const int Multipliers[4] = { 40, 100, 300, 1200 };
}


TetrisGameSession::TetrisGameSession()
    :   m_NextBlock(0),
        m_CurrentBlock(0),
        m_GameGrid(0),
        m_HUD(0),
        m_Background(0),
        m_Engine(0),
        m_iScore(0),
        m_iNumOfLines(0),
        m_iCurrentLevel(1),
        m_TetrisBlockX(0),
        m_TetrisBlockY(0),
        m_bArrowKeyDown(false),
        m_fCurrentFallTime(0.0f),
        m_fLevelBasedFallMultiplier(0.0f),
        m_iMaxFallTime(0)
{
}


TetrisGameSession::~TetrisGameSession()
{     
}

/** 
 * Initializes all member variables. 
 * 
 * @remarks This function <b>must</b> be called before attempting to 
 * run the game. I recommend calling this function as soon as you 
 * declare a TetrisGameSession object. I did this so that re-running
 * a tetris game doesn't involve re-instantiating a new TetrisGameSession
 * object. 
 *
 * @b Example:
 * @code
 *    HGE * engine = 0;                 // uninitialized engine
 *    engine->hgeCreate(HGE_VERSION);   // initialize the engine
 *
 *    TetrisGameSession* game = new TetrisGameSession();   // initialized object, but no reference to the HGE handle
 *    game->Initialize(engine);                              // initialize variables and give the game session a handle to the engine
 *
 * @endcode
 */
void TetrisGameSession::Initialize(HGE* hgeEngine)
{
    // In order for the game to function, we need a valid engine.
    CPAssert( hgeEngine != 0,        "hgeEngine is NULL in TetrisGameSession::Initialize" );

    GameSession::Initialize(hgeEngine);

    // Setup the engine
    m_Engine = hgeEngine;
    hgeEngine->System_SetState( HGE_LOGFILE, "Logs/Tetris.log" );
    hgeEngine->System_SetState( HGE_INIFILE, "Ini/TetrisGame.ini" );

	// Setup default values
    m_iScore		            = 0;
    m_iNumOfLines	            = 0;
    m_iCurrentLevel	            = 1;
    m_bArrowKeyDown	            = false;
    m_fCurrentFallTime          = 0.0f;
    m_fLevelBasedFallMultiplier = 2.0f;
    m_iMaxFallTime	            = 1;
    m_iTenPercentOfMaxFallTime  = TenPercentOfMaxFallTime();

    // Get the starting, top-left vertex position for the top-most block in a TetrisBlock
    // These values are used to determine the initial posiiton when a TetrisBlock is created.
    m_TetrisBlockX = hgeEngine->Ini_GetFloat( TETRIS_BLOCK_SECTION, "StartingTopLeftX", m_TetrisBlockX );
    m_TetrisBlockY = hgeEngine->Ini_GetFloat( TETRIS_BLOCK_SECTION, "StartingTopLeftY", m_TetrisBlockY );

    m_CurrentBlock = CreateNewRandomTetrisBlock();
    if( !m_CurrentBlock )
     return;
     
    m_NextBlock = CreateNewRandomTetrisBlock();
    if( !m_NextBlock )
      return;

    m_GameGrid = new TetrisGrid();

    m_HUD = new TetrisHud();

    CPAssert( m_HUD != 0,           "m_HUD is NULL in TetrisGameSession::Initialize" );
}

void TetrisGameSession::Start(HGE* hgeEngine, hgeResourceManager* ResourceManager)
{
    GameSession::Start( hgeEngine );

    m_HUD->Initialize( hgeEngine, ResourceManager );
}

void TetrisGameSession::Update(float inDeltaTime)
{
    CPAssert(m_CurrentBlock != NULL, "Current Block is NULL in TetrisGameSession::Update");

    GameSession::Update( inDeltaTime );

    ProcessInput();

    m_fCurrentFallTime += (inDeltaTime * m_fLevelBasedFallMultiplier);

    if( m_fCurrentFallTime > m_iMaxFallTime )
    {
        if( !m_GameGrid->WillCollideWithBase(m_CurrentBlock) )
        {
            m_CurrentBlock->MoveDown();
        }
        
        // Handle Collision!
        else
		{
            OnBlockLandedEvent();
		}

        m_fCurrentFallTime = 0.0f;
    }

    m_bGameOver = IsGameOver();
}

void TetrisGameSession::Stop()
{
    GameSession::Stop();

    if( m_NextBlock != NULL )
    {
        delete m_NextBlock;
        m_NextBlock = 0;
    }
    
    if( m_CurrentBlock != NULL )
    {
        delete m_CurrentBlock;  
        m_CurrentBlock = 0;
    }
}


void TetrisGameSession::Render() const
{
    CPAssert( m_NextBlock != 0,     "m_NextBlock is NULL in TetrisGameSession::Render" );
    CPAssert( m_CurrentBlock != 0,  "m_CurrentBlock is NULL in TetrisGameSession::Render" );

    m_HUD->RenderBackground();

    m_HUD->PrintLinesCompleted( m_iNumOfLines );
    m_HUD->PrintPlayerScore( m_iScore );
    m_HUD->PrintPlayerLevel( m_iCurrentLevel );
    m_HUD->RenderNextBlock( m_NextBlock->GetBlockType() );

    m_GameGrid->Render( m_Engine );
    m_CurrentBlock->Render( m_Engine );
}

/**
 * @brief  Handles input events according to the rules of tetris
 * 
 * @author Peter Bennett (curlyhairedgreatness@gmail.com)
 *
 * @return  nothing
 *
 * @remarks A tetris block stops moving left or right as soon as it 
 * collides with a wall. Likewise, the tetris block stops moving 
 * down once it collides with another block or the bottom. 
 * 
 * @b Controls:
 * @code
 *     Left-Arrow Key:      move left
 *     Right-Arrow Key:     move right
 *     Up-Arrow Key:        rotate block 90 degrees clockwise
 *     Down Key:  			
 * @endcode
 *
 */ 
void TetrisGameSession::ProcessInput()
{
    switch(m_Engine->Input_GetKey())
    {
        case HGEK_RIGHT:	  
            if(!m_GameGrid->WillCollideWithRightWall(m_CurrentBlock))
            {
       	        m_CurrentBlock->MoveRight();
            }
            break;

       case HGEK_LEFT:	  
            if(!m_GameGrid->WillCollideWithLeftWall(m_CurrentBlock))
            {
       	        m_CurrentBlock->MoveLeft();
            }
            break;

       case HGEK_UP:
		   if(m_CurrentBlock->CanRotate(*m_GameGrid))
		   {
				m_CurrentBlock->Rotate();
		   }
			break;

       case HGEK_DOWN:
           m_fCurrentFallTime = static_cast<float>(m_iMaxFallTime);
           break;

       default:
           break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Creates a new TetrisBlock of a random type.
 *
 * @remarks This function does not set the newly-created TetrisBlock
 * to the Current or Next TetrisBlock. 
 *
 * @return A pointer to a newly-instantiated TetrisBlock object of a random type. 
 * @see EBlockType
 */
////////////////////////////////////////////////////////////////////////////////////////////
TetrisBlock* TetrisGameSession::CreateNewRandomTetrisBlock()
{
    static Vector2D StartingPosition(m_TetrisBlockX, m_TetrisBlockY);

    EBlockType RandomBlockType = (EBlockType)(rand()%BlockType_Total);
    return TetrisBlockFactory::Create( RandomBlockType, StartingPosition );
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Replaced by the next block in the queue.
 *
 * @remarks The current block is destroyed and replaced with the next block.
 * The next block <b>is not</b> created. 
 */
////////////////////////////////////////////////////////////////////////////////////////////
void TetrisGameSession::ReplaceCurrentBlockWithNextBlock()
{ 
    CPAssert( m_CurrentBlock != NULL, "Current Block is NULL in TetrisGameSession::ReplaceCurrentBlockWithNextBlock");
    // get rid of the current block
    delete m_CurrentBlock;
    m_CurrentBlock = 0;

    m_CurrentBlock = m_NextBlock; 
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Checks game conditions. If the blocks reach
 * reach the top of the screen, the game is over
 * 
 * @return True if blocks reached top of the screen
 */
////////////////////////////////////////////////////////////////////////////////////////////
bool TetrisGameSession::IsGameOver() const
{
    return m_GameGrid->WillCollideWithTop(m_CurrentBlock);
}

////////////////////////////////////////////////////////////////////////////////////////////
/** 
 * Adds points to the player's score based on how many lines completed.
 *
 * @remarks Although I could have just incremented the score in this function
 * since the score in within the score of class, I decided not to in case I 
 * wanted to add some kind of bonus modifier.
 *
 * @param   NumberOfLinesCompleted      The total number of lines completed. 
 * 
 * @return  The score that should be added 
 */
////////////////////////////////////////////////////////////////////////////////////////////
int TetrisGameSession::CalculateScore(int NumberOfLinesCompleted)
{
	CPAssert(NumberOfLinesCompleted > 0, "Invalid value for the number of lines completed");

    return (m_iCurrentLevel * Multipliers[NumberOfLinesCompleted]) + Multipliers[NumberOfLinesCompleted];
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Calculates the current level of the player.
 */
////////////////////////////////////////////////////////////////////////////////////////////
int TetrisGameSession::CalculateLevel() const
{
    // TODO: Figure out the magic number or formula
    return (m_iScore / 200) + 1;
}

int TetrisGameSession::TenPercentOfMaxFallTime() const
{
    return m_iMaxFallTime / 10;
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Handles the event that a block land. The current blocks in the TetrisBlock are disbanned
 * to the Line that they reside on. Also, the player is rewarded points landing a block. 
 * Lastly, this function checks the condition that the landed block completed a line or lines.
 */
////////////////////////////////////////////////////////////////////////////////////////////
void TetrisGameSession::OnBlockLandedEvent()
{
#pragma message("WARNING: TetrisGameSession::BlockLandedEvent() Needs a dereference check")
        m_GameGrid->SnapTetrisBlockToGrid( *m_CurrentBlock );

        // Update Player stats
        // TODO: Replace 5 with variable name. Static variable? Instance variable? Define?
        m_iScore += 5;

        int LinesCompleted = m_GameGrid->GetLinesCompleted();

        if( LinesCompleted > 0 )
		{
            LineCompletedEvent( LinesCompleted );
		}

        m_iCurrentLevel             = CalculateLevel();
        m_iTenPercentOfMaxFallTime  = TenPercentOfMaxFallTime();

        // Clean up
        ReplaceCurrentBlockWithNextBlock();
        m_NextBlock = CreateNewRandomTetrisBlock();
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Handles the situation when a line was completed by requesting the TetrisGrid to clear any
 * completed lines and recalculates the player's score.
 *
 * @param   LinesCompleted  The total number of lines completed. 
 */
////////////////////////////////////////////////////////////////////////////////////////////
void TetrisGameSession::LineCompletedEvent( int LinesCompleted )
{
    CalculateScore( LinesCompleted );
    m_GameGrid->ClearCompletedLines();
}

// EOF
