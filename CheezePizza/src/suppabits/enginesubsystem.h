#ifndef EngineSubsystem_H_
#define EngineSubsystem_H_


// ----------------------------------------------------------------------------
// EngineSubsystem - Defines
// ----------------------------------------------------------------------------

#define DECLARE_SUBSYSTEM(ClassName) \
private: \
	ClassName() {} \
	~ClassName() {} \
	ClassName(const ClassName&); \
	ClassName& operator=(const ClassName&); \
public: \
	static ClassName& Instance() { static ClassName SubInstance; return SubInstance; }

// ----------------------------------------------------------------------------
// EngineSubsystem - Enums
// ----------------------------------------------------------------------------

enum EEngineSubsystemMessages
{
	ESM_Invalid			= 0,
	ESM_GamePaused		= 1,
	ESM_GameResumed		= 2,
	ESM_GameSaved		= 3,
	ESM_GameLoaded		= 4,
	ESM_PlayerSpawned	= 5,
	ESM_Max				= 1000,
};

// ----------------------------------------------------------------------------
// EngineSubsystem - Declaration
// ----------------------------------------------------------------------------

class EngineSubsystem
{
public:
	EngineSubsystem();
	virtual ~EngineSubsystem();

	void Initialize();
	void Shutdown();

	bool IsInitialized() const;

	void OnFirstEngineTick();
	bool HasTicked() const;
	virtual void Tick(float DeltaTime) {}

	virtual void OnAppFocusGained() {}
	virtual void OnAppFocusLost() {}

	virtual void AddObjectsToRenderQueue(class CheezePizzaEngine& Engine) {}

	virtual void HandleMessage(class Message& Msg) {}
	virtual void HandleMessage(class MessageInt& Msg) {}
	virtual void HandleMessage(class MessageFloat& Msg) {}
	virtual void HandleMessage(class MessageBool& Msg) {}
	virtual void HandleMessage(class MessageDouble& Msg) {}
	virtual void HandleMessage(class MessagePointer& Msg) {}

protected:
	virtual void FirstEngineTickInternal() {}
	virtual void InitializeInternal() {}
	virtual void ShutdownInternal() {}

	class HGE* HGEEngine;
	bool bIsInitialized;
	bool bTickedOnce;
};


// ----------------------------------------------------------------------------
// EngineSubsystem - Inline methods
// ----------------------------------------------------------------------------

inline bool EngineSubsystem::HasTicked() const
{
	return bTickedOnce;
}

inline bool EngineSubsystem::IsInitialized() const
{
	return bIsInitialized;
}

#endif