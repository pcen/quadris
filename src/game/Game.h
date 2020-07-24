#ifndef GAME_H
#define GAME_H

#include <string>

#include "../generic/Subject.h"
#include "../controller/Command.h"

class Game: public Subject
{
public:
	Game();
	~Game();
	void update(const Command& command);
	bool isRunning(void) const;

private:
	bool _running;
};

#endif // GAME_H
