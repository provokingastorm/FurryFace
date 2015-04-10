#ifndef TetrisGameSession_H_
#define TetrisGameSession_H_

#ifndef GameSession_H_
#include "gamesession.h"
#endif

class hgeSprite;
class hgeResourceManager;
class TetrisBlock;
class TetrisHud;
class Block;
class TetrisGrid;


class TetrisGameSession : public GameSession
{
private:  
    // GAME AGENTS
    TetrisBlock*	m_NextBlock;
    TetrisBlock*	m_CurrentBlock;

    // WORLD
    TetrisGrid*     m_GameGrid;

    // HUD 
    TetrisHud*		m_HUD;
    hgeSprite*		m_Background;

    // ENGINE
    HGE*			m_Engine;
   
    // PLAYER STATISTICS
    int				m_iScore;
    int             m_iNumOfLines;
    int             m_iCurrentLevel;

    // LOCATION DATA
    float           m_TetrisBlockX;
    float           m_TetrisBlockY;

    // INPUT    
    bool            m_bArrowKeyDown; 

    // TIMING
    float           m_fCurrentFallTime; 
    float           m_fLevelBasedFallMultiplier;
    int             m_iMaxFallTime;
    int             m_iTenPercentOfMaxFallTime;

public:
    TetrisGameSession();
    ~TetrisGameSession();
    
    void            Initialize(HGE* hgeEngine);
    void            Start(HGE* hgeEngine, hgeResourceManager* ResourceManager);
    void            Update(float inDeltaTime);
    void            Stop();
    void            Render() const;

    TetrisBlock*    CreateNewRandomTetrisBlock();
    void            ReplaceCurrentBlockWithNextBlock();
    bool            IsGameOver() const;

    int             GetLinesCompleted() const           { return m_iNumOfLines; };
    int             GetPlayerScore() const              { return m_iScore; };
    int             GetPlayerCurrentLevel() const       { return m_iCurrentLevel; };

private:
    void            ProcessInput();
    int             CalculateScore( int NumberOfLinesCompleted );
    int             CalculateLevel() const;
    int             TenPercentOfMaxFallTime() const;

    // EVENT HANDLERS
    void            OnBlockLandedEvent();
    void            LineCompletedEvent( int LinesCompleted );
    
}; 


#endif
