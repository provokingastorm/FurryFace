#ifndef InputConfig_H_
#define InputConfig_H_

#ifndef Vector_STL_H_
#include <vector>
#endif

// ----------------------------------------------------------------------------
// InputConfig - Declaration
// ----------------------------------------------------------------------------

class InputConfig
{
public:
	InputConfig();
	InputConfig(class LocalPlayer& AssignedPlayer);
	virtual ~InputConfig();

	void SetDeltaTime(float DeltaTime);

	virtual void GetKeyUpEvents(std::vector<int>& KeyUpEvents) {}
	virtual void GetKeyDownEvents(std::vector<int>& KeyDownEvents) {}

	virtual void OnKeyUp(int KeyID) {}
	virtual void OnKeyDown(int KeyID) {}

protected:
	float GetCachedDeltaTime() const;

	class LocalPlayer* Player;

private:
	float CachedDeltaTime;
};

// ----------------------------------------------------------------------------
// InputConfig - Inline methods
// ----------------------------------------------------------------------------

inline float InputConfig::GetCachedDeltaTime() const
{
	return CachedDeltaTime;
}


#endif