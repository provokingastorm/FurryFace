#ifndef InputConfig_H_
#define InputConfig_H_

// ----------------------------------------------------------------------------
// InputConfig - Declaration
// ----------------------------------------------------------------------------

class InputConfig
{
public:
	InputConfig();
	InputConfig(class InputCoordinator& InCoordinator);
	virtual ~InputConfig();

	virtual void HandleInput(float DeltaTime) {}

protected:

	class InputCoordinator* Coordinator;
};


#endif

// EOF
