#ifndef PlayerSubsystem_H_
#define PlayerSubsystem_H_

#ifndef EngineSubsystem_H_
#include "enginesubsystem.h"
#endif

#ifndef Vector_STL_H_
#include <vector>
#endif

// ----------------------------------------------------------------------------
// PlayerSubsystem - Defines
// ----------------------------------------------------------------------------

#define MAX_LOCAL_PLAYERS	4

// ----------------------------------------------------------------------------
// PlayerSubsystem - Enums
// ----------------------------------------------------------------------------

enum ELocalPlayerIndex
{
	LPI_PlayerOne		= 0,
	LPI_PlayerTwo		= 1,
	LPI_PlayerThree		= 2,
	LPI_PlayerFour		= 3
};

// ----------------------------------------------------------------------------
// PlayerSubsystem - Delegates
// ----------------------------------------------------------------------------

struct DelegatePlayer
{
	virtual void Invoke(class LocalPlayer& Player, ELocalPlayerIndex PlayerIndex) {}
};

// ----------------------------------------------------------------------------
// PlayerSubsystem - Declaration
// ----------------------------------------------------------------------------

class PlayerSubsystem : public EngineSubsystem
{
public:
	DECLARE_SUBSYSTEM(PlayerSubsystem);

	void SetPlayerFactory(class PlayerFactory& Factory);
	bool IsLocalPlayerLoggedIn(ELocalPlayerIndex PlayerIndex) const;

	void AddPlayerCreatedDelegate(DelegatePlayer& Delegate);

protected:

	// --------------------------------------------------------
	//	EngineSubsystem inherited methods

	void InitializeInternal();
	void ShutdownInternal();
	void FirstEngineTickInternal();

private:

	void SetupNewLocalPlayer(ELocalPlayerIndex PlayerIndex);

	// Player
	class LocalPlayer* Players[MAX_LOCAL_PLAYERS];
	class PlayerFactory* PlayerCreator;

	// Delegates
	std::vector<DelegatePlayer*> PlayerCreatedDelegates;
};

#endif