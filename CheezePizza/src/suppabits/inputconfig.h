#ifndef InputConfig_H_
#define InputConfig_H_

// ----------------------------------------------------------------------------
// InputConfig - Declaration
// ----------------------------------------------------------------------------

class InputConfig
{
public:
	InputConfig();
	InputConfig(class LocalPlayer& AssignedPlayer);
	virtual ~InputConfig();

	virtual void HandleInput(float DeltaTime) {}

protected:

	class LocalPlayer* Player;
};


#endif