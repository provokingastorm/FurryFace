#ifndef TetrisGameSession_H_
#define TetrisGameSession_H_

#ifndef GameSession_H_
#include "gamesession.h"
#endif


class OriginsGameSession : public GameSession
{
public:
	OriginsGameSession();
	~OriginsGameSession();

	// GameSessions interfaces
	void PreInit();
	void LoadGame();
	char* GetGameName() const;
	char* GetGameShortName() const;
	void OnPlayerCreated(class LocalPlayer& NewPlayer);
};


#endif
