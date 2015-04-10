#ifndef EngineSubsystem_H_
#define EngineSubsystem_H_

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