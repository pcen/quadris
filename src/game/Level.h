#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <fstream>
#include "Game.h"

class Game;

class Level
{
public:
	virtual ~Level() {};
	virtual std::shared_ptr<Block> getNextBlock(void) const = 0;

	int getLevel(void) const { return this->_level; }

protected:
	friend class Game;

	int _level;
	bool _random;
	std::string _filePath;
	std::ifstream _sequence;
	Game* _game;
};

#endif // LEVEL_H
