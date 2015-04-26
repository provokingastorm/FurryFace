#ifndef PlayerFactory_H_
#define PlayerFactory_H_


class PlayerFactory
{
public:
	PlayerFactory(class GameSession& AssignedSession);
	virtual ~PlayerFactory();

	class LocalPlayer* CreateNewPlayer();

protected:
	// Override on derived classes to create game-specific objects
	virtual class LocalPlayer* CreatePlayer();
	virtual class Hud* CreateHud();

private:
	PlayerFactory();

	class GameSession* Session;
};


#endif