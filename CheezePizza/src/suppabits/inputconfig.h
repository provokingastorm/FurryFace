#ifndef InputConfig_H_
#define InputConfig_H_

// ----------------------------------------------------------------------------
// InputConfig - Declaration
// ----------------------------------------------------------------------------

class InputConfig
{
public:

	InputConfig();
	virtual ~InputConfig();

	virtual void HandleInput(float DeltaTime) {}

private:
};


#endif

// EOF
