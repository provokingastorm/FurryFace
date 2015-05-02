#ifndef CheezePizzaEngine_H_
#define CheezePizzaEngine_H_

#ifndef Vector_STL_H_
#include <vector>
#endif


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

	void Initialize(class IPlatform& Platform, char* InGameName, char* InGameShortName);
	void Startup();
	void Shutdown();

	bool Tick();


	// --------------------------------------------------------
	//	Rendering Methods

	void Render();
	// Returns true if the object was added to the render queue; false, otherwise.
	bool AddToRenderQueue(class IRenderable& RenderableObject);

	void OnFocusGained();
	void OnFocusLost();

	bool IsInitialized() const;

	bool IsExiting() const;
	void ExitApplication();

	const char* GetGameName() const { return GameName; }
	const char* GetGameShortName() const { return GameShortName; }

	bool AddEngineSubsystem(class EngineSubsystem& Subsystem);

	class HGE& GetHGE() const;
	class IPlatform& GetPlatform() const;


	// HGE data structures
	class hgeResourceManager* ResourceManager;

private:

	void ImportEngineConfig();

	void OnFirstTick(float DeltaTime);

	// Prevent the functions from getting called since this is a singleton
	CheezePizzaEngine();
	CheezePizzaEngine(const CheezePizzaEngine&);
	CheezePizzaEngine& operator=(const CheezePizzaEngine&);

	std::vector<class IRenderable*> RenderQueue;
	std::vector<class EngineSubsystem*> Subsystems;

	class IPlatform* PlatformInterface;

	// Tick
	bool bTickedOnce;

	// Engine states
	bool bIsHGEInitialized;
	bool bExitApplication;

	// Engine configuration
	char* GameName;
	char* GameShortName;
};


#endif
