#include "tetrisblockt.h"
#include "tetrisblockproxy.h"
#include "block.h"



/*************************
 *       TetrisBlockT          *
 ************************/
TetrisBlockT::TetrisBlockT(float TopLeftPositionX, float TopLeftPositionY)
{
    
    // initializes all the x and y-coordinates
    m_Blocks[0]->SetX( TopLeftPositionX );
    m_Blocks[0]->SetY( TopLeftPositionY );
    m_Blocks[1]->SetX( TopLeftPositionX );
    m_Blocks[1]->SetY( TopLeftPositionY + 17 );
    m_Blocks[2]->SetX( TopLeftPositionX - 17 );
    m_Blocks[2]->SetY( TopLeftPositionY + 17 );
    m_Blocks[3]->SetX( TopLeftPositionX + 17 );
    m_Blocks[3]->SetY( TopLeftPositionY + 17 );
    
    // initializes the line value
    m_Blocks[0]->SetLine(19);
    m_Blocks[1]->SetLine(18);
    m_Blocks[2]->SetLine(18);
    m_Blocks[3]->SetLine(18);
    
    // initializes the line position
    m_Blocks[0]->SetLinePosition(5);
    m_Blocks[1]->SetLinePosition(5);
    m_Blocks[2]->SetLinePosition(4);
    m_Blocks[3]->SetLinePosition(6);
    
    // sets the color of the blocks
    for(int i = 0; i < TetrisBlockSize; i++)
    {
        m_Blocks[i]->SetColor(BLUE);
    }
    
    m_BlockType = BlockType_T;
}

TetrisBlockT::~TetrisBlockT()
{
}

int TetrisBlockT::GetBottomLine() const
{
    int BottomLine = m_Blocks[2]->GetLine();
    
    return BottomLine; 
}

void TetrisBlockT::SimulateRotation(int Rotation, TetrisBlockProxy& OutProxy)
{
    switch( Rotation % 4 )
    {
    case 1:
		{
			int BaseLine = OutProxy.Proxies[1].Line;

			OutProxy.Proxies[0].Position.X += 17;
			OutProxy.Proxies[0].Position.Y -= 17;
			OutProxy.Proxies[0].Line = BaseLine + 1;
	        
			OutProxy.Proxies[2].Position.X -= 17;
			OutProxy.Proxies[2].Position.Y -= 17;
			OutProxy.Proxies[2].Line = BaseLine;
	        
			OutProxy.Proxies[3].Position.X += 17;
			OutProxy.Proxies[3].Position.Y += 17;
			OutProxy.Proxies[3].Line = BaseLine;
	        
			OutProxy.Proxies[0].LinePosition += 1;
			OutProxy.Proxies[2].LinePosition -= 1;
			OutProxy.Proxies[3].LinePosition += 1;
	        
			break;
		}
    case 2:
		{
			int BaseLine = OutProxy.Proxies[1].Line;

			OutProxy.Proxies[2].Position.X += 17;
			OutProxy.Proxies[2].Position.Y += 17;
			OutProxy.Proxies[2].Line = OutProxy.Proxies[1].Line - 1;
	        
			OutProxy.Proxies[2].LinePosition = OutProxy.Proxies[2].LinePosition + 1;
	        
			break;
		}
    case 3:
		{
			int BaseLine = OutProxy.Proxies[1].Line;

			OutProxy.Proxies[0].Position.X -= 17;
			OutProxy.Proxies[0].Position.Y += 17;
			OutProxy.Proxies[0].Line = OutProxy.Proxies[1].Line;
	        
			OutProxy.Proxies[0].LinePosition = OutProxy.Proxies[1].LinePosition - 1;
	        
			break;
		}
    case 0:
		{
			int BaseLine = OutProxy.Proxies[1].Line;

			OutProxy.Proxies[3].Position.X -= 17;
			OutProxy.Proxies[3].Position.Y -= 17;
			OutProxy.Proxies[3].Line = OutProxy.Proxies[1].Line + 1;
	        
			OutProxy.Proxies[3].LinePosition -= 1;
	        
			break;
		}
    default:
        break;
	}   
}

// EOF
