#ifndef GAME_H
#define GAME_H

#include <string>
#include <memory>
#include <vector>

#include "../generic/Subject.h"
#include "../blocks/Board.h"
#include "../controller/Command.h"
#include "Level.h"
#include "StandardLevels.h"

class Level;

class Game: public Subject
{
public:
	Game();
	~Game();
	void update(const Command& command);
	bool isRunning(void) const;

	const Board& getBoard(void) const;

	// gameplay methods
	void launch();
	void restart();
	void quit();
	void levelup();
	void leveldown();
	void score();

private:
	Board _board;
	std::unique_ptr<Level> _level;
	bool _running;
	uint _score;
	uint _highScore;

};

#endif // GAME_H
