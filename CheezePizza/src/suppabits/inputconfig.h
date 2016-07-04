#ifndef InputConfig_H_
#define InputConfig_H_

// ----------------------------------------------------------------------------
// InputConfig - Declaration
// ----------------------------------------------------------------------------

class InputConfig
{
public:
	InputConfig();
	InputConfig(class ActionHandler& InHandler);
	virtual ~InputConfig();

	virtual void HandleInput(float DeltaTime) {}

protected:

	class ActionHandler* Handler;
};


#endif

// EOF
