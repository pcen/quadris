#ifndef GAME_H
#define GAME_H

#include <string>
#include <memory>

#include "../generic/Subject.h"
#include "Board.h"
#include "../controller/Command.h"
#include "../levels/Level.h"
#include "../levels/StandardLevels.h"


class Game: public Subject
{
public:

	Game();
	~Game();
	void update(const Command& command);
	bool isRunning(void) const;

	void launch();
	void restart();
	void quit();
	void levelup();
	void leveldown();
	void score();

private:

	Board _board;
	bool _running;
	std::unique_ptr<Level> _level;
	int _difficulty;
	uint _score;
	uint _highScore;
	bool _random;

};

#endif // GAME_H
