#ifndef _TETRISHUD_H_
#define _TETRISHUD_H_

#ifndef TetrisDefines_H_
#include "defines.h"
#endif 

#include "hgevector.h"

class HGE;
class hgeSprite;
class hgeFont;
class hgeResourceManager;

class TetrisHud
{
private:
    hgeSprite *         m_Background;
    hgeSprite *         m_BlockT;
    hgeSprite *         m_BlockZ;
    hgeSprite *         m_BlockS;
    hgeSprite *         m_BlockO;
    hgeSprite *         m_BlockL;
    hgeSprite *         m_BlockJ;
    hgeSprite *         m_BlockI;
    hgeFont *           m_PrintFont;

    hgeVector           m_LinesCompletedPosition;
    hgeVector           m_PlayerScorePosition;
    hgeVector           m_PlayerLevelPosition;
    hgeVector           m_NextBlockPreviewPosition;

public:
    TetrisHud();
    ~TetrisHud();

    int Initialize( HGE * hgeEngine, hgeResourceManager * ResourceManager );

    void RenderBackground() const;
    void RenderNextBlock( EBlockType BlockType ) const;

    void PrintLinesCompleted( const int LinesCompleted ) const;
    void PrintPlayerScore( const int CurrentScore ) const;
    void PrintPlayerLevel( const int CurrentLevel ) const;

private:
    void LoadBackground( HGE * hgeEngine, hgeResourceManager * ResourceManager );
    void LoadTetrisBlockSprites( HGE * hgeEngine, hgeResourceManager * ResourceManager );
    void LoadHudPositions( HGE * hgeEngine );
};



#endif