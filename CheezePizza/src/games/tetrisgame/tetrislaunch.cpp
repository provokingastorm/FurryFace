#include "cheezepizzaengine.h"
#include "tetrisgamesession.h"
#include <hgeresource.h>
#include <hgesprite.h>
#include <time.h>

HGE*                    g_Engine            = 0;
TetrisGameSession*      g_Tetris            = 0;
HTARGET                 g_Target;
hgeSprite *             g_TargetSprite      = 0;

bool FrameFunc()
{
	float deltaTime = g_Engine->Timer_GetDelta();

	// if ESC key pressed, exit game. Otherwise,
	// the only way to quit the game is through
	// the task manager. ugh.
	if ( g_Engine->Input_GetKeyState(HGEK_ESCAPE) || g_Tetris->IsGameOver() ) 
		return true;

	g_Tetris->Update( deltaTime );

	return false;
}

bool RenderFunc()
{
	g_Engine->Gfx_BeginScene();
	g_Engine->Gfx_Clear(0);
	g_Tetris->Render();
	g_Engine->Gfx_EndScene();


	return false;
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{	
	srand(time(NULL));

	bool WasCreated     = CreateEngine();
	g_Engine            = GetEngine();
	g_Target            = 0;
	g_Tetris            = new TetrisGameSession();

	//////////////////////////////////////////////
	// Configure the system according to our needs
	//////////////////////////////////////////////
	g_Tetris->Initialize(g_Engine);
	// FrameFunc is necessary for the game to run
	g_Engine->System_SetState( HGE_FRAMEFUNC, FrameFunc );
	// RenderFunc is necessary for rendering items to the screen
	g_Engine->System_SetState(HGE_RENDERFUNC, RenderFunc);
	
	if( InitializeEngine() )
	{
		g_Tetris->Start(g_Engine, GetResourceMgr());
		// Create a render target and a sprite for it
		/*g_Target = g_Engine->Target_Create(512, 512, false);
		g_TargetSprite = new hgeSprite(g_Engine->Target_GetTexture(g_Target), 0, 0, 512, 512);
		g_TargetSprite->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);*/
		g_Engine->System_Start();

		// If the program reaches this point, the game is finished.
		// Perform cleanup tasks to release resource to the Operating System
		g_Tetris->Stop();
		delete g_Tetris;
		delete g_TargetSprite;
		//g_Engine->Target_Free(g_Target);
	}

	g_Engine->System_Shutdown();
	g_Engine->Release();

	return 0;
}
