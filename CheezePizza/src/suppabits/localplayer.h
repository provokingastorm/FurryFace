#ifndef LocalPlayer_H_
#define LocalPlayer_H_

class LocalPlayer
{
public:
	LocalPlayer();
	virtual ~LocalPlayer();

	void SetHUD(class Hud& NewHud);
	void OnCreated();

protected:
	virtual void OnCreatedInternal() {}

private:
	class Hud* GameHud;
};

#endif