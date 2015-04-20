#ifndef EngineSubsystem_H_
#define EngineSubsystem_H_

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

class EngineSubsystem
{
public:
	EngineSubsystem();
	virtual ~EngineSubsystem();

	void Initialize();
	void Shutdown();

	bool IsInitialized() const;

	virtual void AddObjectsToRenderQueue(class CheezePizzaEngine& Engine) {}
	virtual void OnFirstEngineTick() {}

	virtual void HandleMessage(class Message& Msg) {}
	virtual void HandleMessage(class MessageInt& Msg) {}
	virtual void HandleMessage(class MessageFloat& Msg) {}
	virtual void HandleMessage(class MessageBool& Msg) {}
	virtual void HandleMessage(class MessageDouble& Msg) {}
	virtual void HandleMessage(class MessagePointer& Msg) {}

protected:
	virtual void InitializeInternal() {}
	virtual void ShutdownInternal() {}

	class HGE* HGEEngine;
	bool bIsInitialized;
};


inline bool EngineSubsystem::IsInitialized() const
{
	return bIsInitialized;
}

#endif