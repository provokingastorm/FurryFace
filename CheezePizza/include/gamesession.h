#ifndef GameSession_H_
#define GameSession_H_

#define IMPLEMENT_SESSION_CREATOR(SessionClass) \
GameSession* CreateGameSession() \
{ \
	return new SessionClass(); \
}

enum EEngineEvent
{
	EE_None			= 0,
	EE_Tick			= 1,
	EE_Render		= 2,
	EE_Exit			= 3,
	EE_FocusGained	= 4,
	EE_FocusLost	= 5,
	EE_MAX			= 6
};

class GameSession
{
public:
    GameSession();
    virtual ~GameSession();
    
    void Initialize();
    void Startup();
	void Shutdown();
	bool RouteEngineEvent(EEngineEvent Event);

    bool IsGameOver() const     { return bGameOver; }
	void GameOver()				{ bGameOver = true; }

	bool IsGamePaused() const   { return bPaused; }
	void Pause();

	// Override on derived classes to setup a game-specific player
	virtual void OnPlayerCreated(class LocalPlayer& NewPlayer)	{}

protected:
	// Override on derived classes to provide game-specific engine configuration
	virtual void PreInit() {}

	// Override on derived classes to provide game-specific startup operations
	virtual void LoadGame() {}

	// Override on derived classes to perform any shutdown tasks like deleting objects
	virtual void ShutdownInernal() {}

	// Override on derived classes to customize the engine output files and game title to your game name
	virtual char* GetGameName() const;
	virtual char* GetGameShortName() const;

	class CheezePizzaEngine* CheezeEngine;
	class HGE* HGEEngine;

private:
	bool bGameOver;
	bool bPaused;
};


// ----------------------------------------------------------------------------
// GameSession - Inline Methods
// ----------------------------------------------------------------------------

inline char* GameSession::GetGameName() const
{
	return "Cheeze Pizza Engine";
}

inline char* GameSession::GetGameShortName() const
{
	return "Cheeze";
}


#endif