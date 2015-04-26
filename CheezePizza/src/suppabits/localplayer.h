#ifndef LocalPlayer_H_
#define LocalPlayer_H_

class LocalPlayer
{
public:
	LocalPlayer();
	virtual ~LocalPlayer();

	void SetHUD(class Hud& NewHud);
	void AssignToSession(class GameSession& NewSession);
	void OnCreated();

protected:
	virtual void OnCreatedInternal() {}

private:
	class GameSession* Session;
	class Hud* GameHud;
};

#endif