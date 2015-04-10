#ifndef Line_H_
#define Line_H_

#include "uncopyable.h"


class   Block;
struct  Point;
class   HGE;

static const int LineSize = 10;

class Line : private Uncopyable
{
private:

    Block *     m_Blocks[LineSize];                   
    int         m_iActiveBlockCount;  
    Point &     Position;

public:

    Line();                                     
    ~Line();                                   
    
    void    Render( HGE * hgeEngine ) const;

    bool    IsFilled() const;                      
    bool    IsEmpty() const;               
    void    Clear();
    void    AddBlock( int Index, Block * inBlock );   
    bool    CanAddBlockToLine( const Block& BlockToAdd ) const;
    
    /** 
     * Returns the number of <b>active</b> blocks in the line 
     * @remarks This does not return the number of total block possible in the line.
     */
    int     GetCurrentSize()            { return m_iActiveBlockCount; };  

    // Remove? This kinda breaks encapsulation.
    Block*  GetBlockAt( int Index )  { return m_Blocks[Index]; };   

    bool    IsBlockAtPosition(int Position) const;             
    void    RemoveBlock( int Index );   
    void    SubtractLineIndex( int TotalIndicies );                                   

private:
    int     GetLinePosition( const Block& InBlock );
};

#endif
