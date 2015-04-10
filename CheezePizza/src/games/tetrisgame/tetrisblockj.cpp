#include "tetrisblockj.h"
#include "tetrisblockproxy.h"
#include "block.h"


TetrisBlockJ::TetrisBlockJ(float TopLeftPositionX, float TopLeftPositionY)
{
    // initializes all the x and y-coordinates
    m_Blocks[0]->SetX( TopLeftPositionX );
    m_Blocks[0]->SetY( TopLeftPositionY + 17 );
    m_Blocks[1]->SetX( TopLeftPositionX );
    m_Blocks[1]->SetY( TopLeftPositionY );
    m_Blocks[2]->SetX( TopLeftPositionX + 17 );
    m_Blocks[2]->SetY( TopLeftPositionY + 17 );
    m_Blocks[3]->SetX( TopLeftPositionX + 34 );
    m_Blocks[3]->SetY( TopLeftPositionY + 17 );
        
    // initializes the line value
    m_Blocks[0]->SetLine(18);
    m_Blocks[1]->SetLine(19);
    m_Blocks[2]->SetLine(18);
    m_Blocks[3]->SetLine(18);
    
    // initializes the line position
    m_Blocks[0]->SetLinePosition(5);
    m_Blocks[1]->SetLinePosition(5);
    m_Blocks[2]->SetLinePosition(6);
    m_Blocks[3]->SetLinePosition(7);
    
    // sets the color of the blocks
    for(int i = 0; i < TetrisBlockSize; i++)
    {
        m_Blocks[i]->SetColor(PINK);
    }
    
    m_BlockType = BlockType_J;
}

TetrisBlockJ::~TetrisBlockJ()
{
}

int TetrisBlockJ::GetBottomLine() const
{
    int BottomLine = 0;
    
    switch(m_Rotation%4)
    {
        case 0:
                BottomLine = m_Blocks[0]->GetLine();
                break;
        case 1:
                BottomLine = m_Blocks[3]->GetLine();
                break;
        case 2:
                BottomLine = m_Blocks[3]->GetLine();
                break;
        case 3:
                BottomLine = m_Blocks[1]->GetLine();
                break;
        default:
                break;
    }

    return BottomLine; 
}

void TetrisBlockJ::SimulateRotation(int Rotation, TetrisBlockProxy& OutProxy)
{
    switch( Rotation % 4 )
    {
    case 1:
		{
			OutProxy.Proxies[0].Position.X -= 17;
			OutProxy.Proxies[0].Position.Y -= 17;
			OutProxy.Proxies[0].Line += 1;

			const int BaseLine = OutProxy.Proxies[0].Line;
	    
			OutProxy.Proxies[1].Position.X -= 17;
			OutProxy.Proxies[1].Position.Y -= 17;
			OutProxy.Proxies[1].Line = BaseLine + 1;
	        
			OutProxy.Proxies[2].Position.X += 17;
			OutProxy.Proxies[2].Position.Y -= 17;
			OutProxy.Proxies[2].Line = BaseLine;
	        
			OutProxy.Proxies[3].Position.X += 17;
			OutProxy.Proxies[3].Position.Y += 17;
			OutProxy.Proxies[3].Line = BaseLine;
	        
			OutProxy.Proxies[0].LinePosition -= 1;

			const int BaseLinePosition = OutProxy.Proxies[0].LinePosition;

			OutProxy.Proxies[1].LinePosition = BaseLinePosition;
			OutProxy.Proxies[2].LinePosition = BaseLinePosition + 1;
			OutProxy.Proxies[3].LinePosition = BaseLinePosition + 2;
	        
			break;
		}
    case 2:
		{
			const int BaseLine = OutProxy.Proxies[0].Line;
	        
			OutProxy.Proxies[1].Position.Y += 34;
			OutProxy.Proxies[1].Line = BaseLine - 1;
	        
			OutProxy.Proxies[3].Position.X -= 34;
			OutProxy.Proxies[3].Position.Y += 34;
			OutProxy.Proxies[3].Line = BaseLine - 2;
	        
			OutProxy.Proxies[3].LinePosition = OutProxy.Proxies[0].LinePosition;
	        
			break;
		}
    case 3:
		{
			const int BaseLine = OutProxy.Proxies[0].Line;
	        
			OutProxy.Proxies[2].Position.X -= 34;
			OutProxy.Proxies[2].Line = BaseLine;
	        
			OutProxy.Proxies[3].Position.X -= 34;
			OutProxy.Proxies[3].Position.Y -= 34;
			OutProxy.Proxies[3].Line = BaseLine;

			const int BaseLinePosition = OutProxy.Proxies[0].LinePosition;
	        
			OutProxy.Proxies[2].LinePosition = BaseLinePosition - 1;
			OutProxy.Proxies[3].LinePosition = BaseLinePosition - 2;
	        
			break;
		}
    case 0:
		{
			const int BaseLine = OutProxy.Proxies[0].Line;
	        
			OutProxy.Proxies[1].Position.Y -= 34;
			OutProxy.Proxies[1].Line = BaseLine + 1;
	        
			OutProxy.Proxies[3].Position.X += 34;
			OutProxy.Proxies[3].Position.Y -= 34;
			OutProxy.Proxies[3].Line = BaseLine + 2;
	        
			OutProxy.Proxies[3].LinePosition = OutProxy.Proxies[0].LinePosition;
	        
			break;
		}
    default:
        break;
    }
}

// EOF
