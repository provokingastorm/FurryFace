#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "defines.h"
#include "uncopyable.h"

#ifndef HGE_H
#include "hge.h"
#endif

/** The total width of the block */
#define BLOCK_WIDTH 16                
/** The total height of the block */
#define BLOCK_HEIGHT 16                                     

class Block
{
    /** Contians he x and y-coordinates (verticies) of the block plus blending options */
    hgeQuad     m_BlockQuad;              
    /** The width of the block */
    int         m_iWidth;
    /** The height of the block */
    int         m_iHeight;   
    /** The line the block is located */
    int         m_iLineIndex; 
    /** The position of the block in the line */
    int         m_iLinePosition;   
    /** The color of the block */
    DWORD       m_Color;    
    
public:

    Block( float TopLeftX, float TopLeftY );  
    ~Block();        

    void Render( HGE * hgeEngine ) const; 
    
     /** @return the width of this block in pixels */
    int GetWidth() const        { return m_iWidth; };    
    /** @return the height of this block */
    int GetHeight() const       { return m_iHeight; };    
    /** @return the x-coordinate of the upper left-hand corner of the block */
    float GetX() const            { return m_BlockQuad.v[0].x; };     
    /** @return the y-coordinate of the upper left-hand corner of the block */
    float GetY() const            { return m_BlockQuad.v[0].y; };           
    /** @return the line that the block is on */
    int GetLine() const         { return m_iLineIndex; };         
    /** @return the position in the line */
    int GetLinePosition() const { return m_iLinePosition; };               
    
    /** Resets the x-coordinate */
    inline void SetX(float TopLeftX);        
    /** Resets the y-coordinate */
    inline void SetY(float TopLeftY);  
    /** Resets the color of the block */
    void SetColor(DWORD Color);   
    /** Resets the line the block is at */
    void SetLine(int Index) { m_iLineIndex = Index; };       
    /** Resets the position in the line */
    void SetLinePosition(int Index) { m_iLinePosition = Index; }; 
    /** Alters the position of the x-coordinate by the value whether positive or negative */
    inline void ChangeXPosition(float TopLeftX);        
    /** Alters the position of the y-coordinate by the value whether positive or negative */
    inline void ChangeYPosition(float TopLeftY);   
    /** Decreaments the line the block resides */
    void UpdateLine() { m_iLineIndex--; };    

    void CopyInto( Block & outBlock );
    
    void MoveDown();                                        /** changes the y-coordinate */
    void MoveDown( int LineIndicies );
    void MoveLeft();                                        /** changes the x-coordinate */
    void MoveRight();                                       /** changes the x-coordinate */

private:
};

void Block::SetX(float TopLeftX)
{
    m_BlockQuad.v[0].x = TopLeftX;
    m_BlockQuad.v[1].x = TopLeftX + m_iWidth;
    m_BlockQuad.v[2].x = TopLeftX + m_iWidth;
    m_BlockQuad.v[3].x = TopLeftX;
}

void Block::SetY(float TopLeftY)
{    
    m_BlockQuad.v[0].y = TopLeftY;
    m_BlockQuad.v[1].y = TopLeftY;
    m_BlockQuad.v[2].y = TopLeftY + m_iHeight;
    m_BlockQuad.v[3].y = TopLeftY + m_iHeight;
}

void Block::ChangeXPosition(float TopLeftX)
{
    m_BlockQuad.v[0].x += TopLeftX;
    m_BlockQuad.v[1].x += TopLeftX;
    m_BlockQuad.v[2].x += TopLeftX;
    m_BlockQuad.v[3].x += TopLeftX;
}

void Block::ChangeYPosition(float TopLeftY)
{
    m_BlockQuad.v[0].y += TopLeftY;
    m_BlockQuad.v[1].y += TopLeftY;
    m_BlockQuad.v[2].y += TopLeftY;
    m_BlockQuad.v[3].y += TopLeftY;
}

#endif

