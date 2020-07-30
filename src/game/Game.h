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

class Game: public Subject
{
public:
	Game();
	~Game();
	void update(const Command& command);
	bool isRunning(void) const;

	const Board& getBoard(void) const;
	const std::vector<Coord> getBoardChanges(void);

	// gameplay methods
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
