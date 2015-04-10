#include "tetrisblockproxy.h"
#include "tetrisgrid.h"
#include "block.h"

TetrisBlockProxy::TetrisBlockProxy(Block* Blocks[TetrisBlockSize])
{
    for( int ProxyIndex = 0; ProxyIndex < TetrisBlockSize; ++ProxyIndex )
    {
        Proxies[ProxyIndex].Position.X		= Blocks[ProxyIndex]->GetX();
        Proxies[ProxyIndex].Position.Y		= Blocks[ProxyIndex]->GetY();
        Proxies[ProxyIndex].Line			= Blocks[ProxyIndex]->GetLine();
        Proxies[ProxyIndex].LinePosition	= Blocks[ProxyIndex]->GetLinePosition();
    }
}

TetrisBlockProxy::~TetrisBlockProxy()
{
}


bool TetrisBlockProxy::WillBlocksCollideWithGrid(const TetrisGrid& InGrid)
{
    for( int ProxyIndex = 0; ProxyIndex < TetrisBlockSize; ++ProxyIndex )
    {
		if(InGrid.IsBlockOutsideGrid( Proxies[ProxyIndex].Line, Proxies[ProxyIndex].LinePosition ))
		{
			return false;
		}

        if(InGrid.IsBlockAtPosition( Proxies[ProxyIndex].Line, Proxies[ProxyIndex].LinePosition ))
        {
            return false;
        }
    }

    // If we made it here, than the tetris block won't collide with the grid
    return true;
}

// EOF
