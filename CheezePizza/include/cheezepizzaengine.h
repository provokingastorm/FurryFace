#ifndef CheezePizzaEngine_H_
#define CheezePizzaEngine_H_

#ifndef Vector_STL_H_
#include <vector>
#endif


#define MAX_LOCAL_PLAYERS	4

typedef void (*CPCallback)();

enum ELocalPlayerIndex
{
	LPI_PlayerOne		= 0,
	LPI_PlayerTwo		= 1,
	LPI_PlayerThree		= 2,
	LPI_PlayerFour		= 3
};

enum EResourceGroup
{
	RG_None			= 0,
	RG_AlwaysLoaded = 1,
};


class CheezePizzaEngine
{
public:
	static inline CheezePizzaEngine& Instance()
	{
		static CheezePizzaEngine Instance;
		return Instance;
	}
	~CheezePizzaEngine();

	void Initialize(char* InGameName, char* InGameShortName);
	void Startup();
	void Shutdown();

	bool Tick();
	void Render();

	void OnFocusGained();
	void OnFocusLost();

	bool IsInitialized() const;

	// HGE data structures
	class HGE* HGEEngine;
	class hgeResourceManager* ResourceManager;

	// Engine subsystems
	class InputSubsystem* InputSub;
	class World2D* World;

	const char* GetGameName() const { return GameName; }
	const char* GetGameShortName() const { return GameShortName; }

	void SetPlayerFactory(class PlayerFactory* Factory);
	bool IsLocalPlayerLoggedIn(ELocalPlayerIndex PlayerIndex) const;

	bool AddEngineSubsystem(class EngineSubsystem& Subsystem);

	void SetFirstTickCallback(CPCallback Callback) { FirstTickCallback = Callback; }

	// Returns true if the object was added to the render queue; false, otherwise.
	bool AddToRenderQueue(class IRenderable& RenderableObject);

private:

	void ImportEngineConfig();
	void OnFirstTick(float DeltaTime);

	void SetupNewLocalPlayer(ELocalPlayerIndex PlayerIndex);

	// Prevent the functions from getting called since this is a singleton
	CheezePizzaEngine();
	CheezePizzaEngine(const CheezePizzaEngine&);
	CheezePizzaEngine& operator=(const CheezePizzaEngine&);

	// Player
	class LocalPlayer* Players[MAX_LOCAL_PLAYERS];
	class PlayerFactory* PlayerCreator;

	std::vector<class IRenderable*> RenderQueue;
	std::vector<class EngineSubsystem*> Subsystems;

	// Engine states
	bool bIsHGEInitialized;
	bool bTickedOnce;
	CPCallback FirstTickCallback;

	// Engine configuration
	char* GameName;
	char* GameShortName;
};


#endif
