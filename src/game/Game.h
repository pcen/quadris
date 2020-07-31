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
	Game(uint, std::string);
	~Game();
	void update(const Command& command);
	bool isRunning(void) const;

	const Board& getBoard(void) const;

	// gameplay methods
	void launch(void);
	void restart(void);
	void quit(void);
	void levelup(void);
	void leveldown(void);
	void score(void);

	int getNumBlocksSinceClear(void);

private:
	void _updateScore(void);

	Board _board;
	std::unique_ptr<Level> _level;
	bool _running;
	uint _score;
	uint _highScore;

	uint _startLevel;
};

#endif // GAME_H
