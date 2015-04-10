#include "tetrisblockz.h"
#include "tetrisblockproxy.h"
#include "block.h"


TetrisBlockZ::TetrisBlockZ( float TopLeftPositionX, float TopLeftPositionY )
{
    // initializes all the x and y-coordinates
    m_Blocks[0]->SetX( TopLeftPositionX );
    m_Blocks[0]->SetY( TopLeftPositionY );
    m_Blocks[1]->SetX( TopLeftPositionX - 17 );
    m_Blocks[1]->SetY( TopLeftPositionY );
    m_Blocks[2]->SetX( TopLeftPositionX + 17 );
    m_Blocks[2]->SetY( TopLeftPositionY + 17 );
    m_Blocks[3]->SetX( TopLeftPositionX );
    m_Blocks[3]->SetY( TopLeftPositionY + 17 );
        
    // initializes the line value
    m_Blocks[0]->SetLine(19);
    m_Blocks[1]->SetLine(19);
    m_Blocks[2]->SetLine(18);
    m_Blocks[3]->SetLine(18);
    
    // initializes the line position
    m_Blocks[0]->SetLinePosition(5);
    m_Blocks[1]->SetLinePosition(4);
    m_Blocks[2]->SetLinePosition(6);
    m_Blocks[3]->SetLinePosition(5);
    
    // sets the color of the blocks
    for(int i = 0; i < TetrisBlockSize; i++)
    {
        m_Blocks[i]->SetColor(ORANGE);
    }
    
    m_BlockType = BlockType_Z;
}

TetrisBlockZ::~TetrisBlockZ()
{
}

int TetrisBlockZ::GetBottomLine() const
{
    int BottomLine = 0;
    
    switch( m_Rotation % 4 )
    {
        case 0:
                BottomLine = m_Blocks[3]->GetLine();
                break;
        case 1:
                BottomLine = m_Blocks[3]->GetLine();
                break;
        case 2:
                BottomLine = m_Blocks[2]->GetLine();
                break;
        case 3:
                BottomLine = m_Blocks[0]->GetLine();
                break;
        default:
                break;
    }
    
    return BottomLine; 
}

void TetrisBlockZ::SimulateRotation(int Rotation, TetrisBlockProxy& OutProxy)
{
    switch( Rotation % 4 )
    {
    case 1:
		{
			const int BaseLine = OutProxy.Proxies[0].Line;

			OutProxy.Proxies[1].Position.X -= 34;
			OutProxy.Proxies[1].Line = BaseLine;
	        
			OutProxy.Proxies[2].Position.Y += 34;
			OutProxy.Proxies[2].Line = BaseLine - 1;
	        
			OutProxy.Proxies[1].LinePosition = OutProxy.Proxies[0].LinePosition - 1;
	        
			break;
		}
    case 2:
		{
			const int BaseLine = OutProxy.Proxies[0].Line;

			OutProxy.Proxies[3].Position.Y -= 34;
			OutProxy.Proxies[3].Line = BaseLine + 1;
	    
			OutProxy.Proxies[2].Position.X -= 34;
			OutProxy.Proxies[2].Line = BaseLine - 1;
	        
			OutProxy.Proxies[2].LinePosition = OutProxy.Proxies[0].LinePosition - 1;
	        
			break;
		}
    case 3:
		{
			const int BaseLine = OutProxy.Proxies[0].Line;

			OutProxy.Proxies[1].Position.X += 34;
			OutProxy.Proxies[1].Line = BaseLine;
	        
			OutProxy.Proxies[2].Position.Y -= 34;
			OutProxy.Proxies[2].Line = BaseLine + 1;
	        
			OutProxy.Proxies[1].LinePosition = OutProxy.Proxies[0].LinePosition + 1;
	    
			break;
		}
    case 0:
		{
			const int BaseLine = OutProxy.Proxies[0].Line;

			OutProxy.Proxies[2].Position.X += 34;
			OutProxy.Proxies[2].Line = BaseLine + 1;
	    
			OutProxy.Proxies[3].Position.Y += 34;
			OutProxy.Proxies[3].Line = BaseLine - 1;
	        
			OutProxy.Proxies[2].LinePosition = OutProxy.Proxies[0].LinePosition + 1;
	        
			break;
		}
    default:
        break;
    }
}

// EOF
