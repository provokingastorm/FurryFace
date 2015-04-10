#include "tetrishud.h"
#include "hge.h"
#include "hgeresource.h"
#include "hgefont.h"


#define TETRIS_HUD_SECTION "TetrisHUD"


////////////////////////////////////////////////////////////////////////////////////////////
// Default Constructor
////////////////////////////////////////////////////////////////////////////////////////////
TetrisHud::TetrisHud()
:m_Background(NULL),
m_BlockT(NULL),
m_BlockZ(NULL),
m_BlockS(NULL),
m_BlockO(NULL),
m_BlockL(NULL),
m_BlockJ(NULL),
m_BlockI(NULL),
m_PrintFont(NULL),
m_LinesCompletedPosition(0.0f, 0.0f),
m_PlayerScorePosition(0.0f, 0.0f),
m_PlayerLevelPosition(0.0f, 0.0f),
m_NextBlockPreviewPosition(0.0f, 0.0f)
{
}

////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////////////////////////////////////////////////
TetrisHud::~TetrisHud()
{

}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Initializes all the elements of the Tetris Hud. <b>This function must be called before
 * using this class</b>. The Tetris background, "Next" block sprites, Hud positions, and
 * Hud fonts are loaded in this function.
 * 
 * @remarks The reason why this functionality isn't in the constructor to delay to 
 * loading of the resources. This gives the user the option of deciding when to load
 * these resources. 
 */
////////////////////////////////////////////////////////////////////////////////////////////
int TetrisHud::Initialize( HGE * hgeEngine, hgeResourceManager * ResourceManager )
{
    LoadBackground( hgeEngine, ResourceManager );
    LoadTetrisBlockSprites( hgeEngine, ResourceManager );
    LoadHudPositions( hgeEngine );

    // Get the Hud font.
    m_PrintFont = ResourceManager->GetFont("CourierNew");
    
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Renders the background (and only the background) to the screen. 
 */
////////////////////////////////////////////////////////////////////////////////////////////
void TetrisHud::RenderBackground() const
{
    if(m_Background)
        m_Background->Render(0,0);
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Renders the next block preview (and only the next block) to the screen. 
 *
 * @param BlockType     The type of block of the next block. 
 */
////////////////////////////////////////////////////////////////////////////////////////////
void TetrisHud::RenderNextBlock( EBlockType BlockType ) const
{
    switch( BlockType)
    {
    case BlockType_T:
        m_BlockT->Render( m_NextBlockPreviewPosition.x, m_NextBlockPreviewPosition.y );
        break;
    case BlockType_Z:
        m_BlockZ->Render( m_NextBlockPreviewPosition.x, m_NextBlockPreviewPosition.y );
        break;
    case BlockType_S:
        m_BlockS->Render( m_NextBlockPreviewPosition.x, m_NextBlockPreviewPosition.y );
        break;
    case BlockType_O:
        m_BlockO->Render( m_NextBlockPreviewPosition.x, m_NextBlockPreviewPosition.y );
        break;
    case BlockType_L:
        m_BlockL->Render( m_NextBlockPreviewPosition.x, m_NextBlockPreviewPosition.y );
        break;
    case BlockType_J:
        m_BlockJ->Render( m_NextBlockPreviewPosition.x, m_NextBlockPreviewPosition.y );
        break;
    case BlockType_I:
        m_BlockI->Render( m_NextBlockPreviewPosition.x, m_NextBlockPreviewPosition.y );
        break;
    default:
        // TODO: add a log message here explaining that a block type wasn't found. 
        break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Prints the number of given lines completed by the player using the Hud font and the
 * pre-defined coordinates loaded from TetrisHud::LoadHudPositions.
 */
////////////////////////////////////////////////////////////////////////////////////////////
void TetrisHud::PrintLinesCompleted( const int LinesCompleted ) const
{
    m_PrintFont->printf( m_LinesCompletedPosition.x, m_LinesCompletedPosition.y, HGETEXT_LEFT, "%d", LinesCompleted );
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Prints the given player score to the screen using the Hud font and the
 * pre-defined coordinates loaded from TetrisHud::LoadHudPositions.
 */
////////////////////////////////////////////////////////////////////////////////////////////
void TetrisHud::PrintPlayerScore( const int CurrentScore ) const
{
    m_PrintFont->printf( m_PlayerScorePosition.x, m_PlayerScorePosition.y, HGETEXT_LEFT, "%d", CurrentScore );
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Prints the given player level to the screen using the Hud font and the
 * pre-defined coordinates loaded from TetrisHud::LoadHudPositions.
 */
////////////////////////////////////////////////////////////////////////////////////////////
void TetrisHud::PrintPlayerLevel( const int CurrentLevel ) const
{    
    m_PrintFont->printf( m_PlayerLevelPosition.x, m_PlayerLevelPosition.y, HGETEXT_LEFT, "%d", CurrentLevel );
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Loads the background for the game. 
 */
////////////////////////////////////////////////////////////////////////////////////////////
void TetrisHud::LoadBackground( HGE * hgeEngine, hgeResourceManager * ResourceManager )
{
    HTEXTURE BackgroundTexture = ResourceManager->GetTexture( "texBackground" );
    int BackgroundWidth = hgeEngine->Texture_GetWidth(BackgroundTexture);
    int BackgroundHeight = hgeEngine->Texture_GetHeight(BackgroundTexture);

    HTARGET BackgroundTarget = hgeEngine->Target_Create( BackgroundWidth, BackgroundHeight, false );

    m_Background = new hgeSprite(BackgroundTexture, 0.0f, 0.0f, static_cast<float>(BackgroundWidth), static_cast<float>(BackgroundHeight) );
    m_Background->SetBlendMode( BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE );
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 *
 */
////////////////////////////////////////////////////////////////////////////////////////////
void TetrisHud::LoadTetrisBlockSprites( HGE * hgeEngine, hgeResourceManager * ResourceManager )
{
    m_BlockT = ResourceManager->GetSprite( "sprTBlock" );
    m_BlockZ = ResourceManager->GetSprite( "sprZBlock" );
    m_BlockS = ResourceManager->GetSprite( "sprSBlock" );
    m_BlockO = ResourceManager->GetSprite( "sprOBlock" );
    m_BlockL = ResourceManager->GetSprite( "sprLBlock" );
    m_BlockJ = ResourceManager->GetSprite( "sprJBlock" );
    m_BlockI = ResourceManager->GetSprite( "sprIBlock" );
}

////////////////////////////////////////////////////////////////////////////////////////////
/**
 *
 */
////////////////////////////////////////////////////////////////////////////////////////////
void TetrisHud::LoadHudPositions(  HGE * hgeEngine )
{
    
    hgeEngine->System_SetState( HGE_INIFILE, "Ini/TetrisEngine.ini" );

    m_LinesCompletedPosition.x = hgeEngine->Ini_GetFloat( TETRIS_HUD_SECTION, "LinesCompletedX", m_LinesCompletedPosition.x );
    m_LinesCompletedPosition.y = hgeEngine->Ini_GetFloat( TETRIS_HUD_SECTION, "LinesCompletedY", m_LinesCompletedPosition.y );

    m_PlayerScorePosition.x = hgeEngine->Ini_GetFloat( TETRIS_HUD_SECTION, "PlayerScoreX", m_PlayerScorePosition.x );
    m_PlayerScorePosition.y = hgeEngine->Ini_GetFloat( TETRIS_HUD_SECTION, "PlayerScoreY", m_PlayerScorePosition.y );

    m_PlayerLevelPosition.x = hgeEngine->Ini_GetFloat( TETRIS_HUD_SECTION, "PlayerLevelX", m_PlayerLevelPosition.x );
    m_PlayerLevelPosition.y = hgeEngine->Ini_GetFloat( TETRIS_HUD_SECTION, "PlayerLevelY", m_PlayerLevelPosition.y );

    m_NextBlockPreviewPosition.x = hgeEngine->Ini_GetFloat( TETRIS_HUD_SECTION, "NextBlockPreviewX", m_NextBlockPreviewPosition.x );
    m_NextBlockPreviewPosition.y = hgeEngine->Ini_GetFloat( TETRIS_HUD_SECTION, "NextBlockPreviewY", m_NextBlockPreviewPosition.y );
}