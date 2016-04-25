#ifndef InputConfig_H_
#define InputConfig_H_

// ----------------------------------------------------------------------------
// InputConfig - Declaration
// ----------------------------------------------------------------------------

class InputConfig
{
public:
	InputConfig();
	InputConfig(class InputHandler& InHandler);
	virtual ~InputConfig();

	virtual void HandleInput(float DeltaTime) {}

protected:

	class InputHandler* Handler;
};


#endif

// EOF
