#ifndef InputConfig_H_
#define InputConfig_H_

#ifndef Vector_STL_H_
#include <vector>
#endif

class InputConfig
{
public:
	InputConfig();
	InputConfig(class LocalPlayer& AssignedPlayer);
	virtual ~InputConfig();

	virtual void GetKeyUpEvents(std::vector<int>& KeyUpEvents) {}
	virtual void GetKeyDownEvents(std::vector<int>& KeyDownEvents) {}

	virtual void OnKeyUp(int KeyID) {}
	virtual void OnKeyDown(int KeyID) {}

protected:
	class LocalPlayer* Player;

private:
};


#endif