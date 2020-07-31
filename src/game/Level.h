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
	virtual std::shared_ptr<Block> getNextBlock(void) = 0;

	int getLevel(void) const;
	void closeSequence(void);
	void openSequence(const std::string& sequenceFile);
	virtual void useRandom(bool random);

protected:
	friend class Game;

	int _level;
	bool _random;
	std::string _filePath;
	std::shared_ptr<std::ifstream> _sequence;
	Game* _game;
};


class LevelFactoryInitializer
{
private:
	static LevelFactoryInitializer lfi;

	LevelFactoryInitializer();
	~LevelFactoryInitializer() {};
};


class LevelFactory
{
public:
	virtual ~LevelFactory() {};
	static std::unique_ptr<Level> createLevel(const int&, std::string, Game*, bool, std::shared_ptr<std::ifstream>);

private:
	friend class LevelFactoryInitializer;
	static std::map<int, std::unique_ptr<LevelFactory>> _factories;
	virtual std::unique_ptr<Level> create(std::string, Game*, bool, std::shared_ptr<std::ifstream>) = 0;
};

#endif // LEVEL_H
