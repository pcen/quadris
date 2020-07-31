#include <assert.h>
#include <iostream>
#include <map>

#include "StandardLevels.h"

// define static instances
std::map<int, std::unique_ptr<LevelFactory>> LevelFactory::_factories;
LevelFactoryInitializer LevelFactoryInitializer::lfi;

// base class level methods
int Level::getLevel(void) const
{
	return this->_level;
}

void Level::closeSequence(void)
{
	if (this->_sequence->is_open())
		this->_sequence->close();
}

void Level::openSequence(const std::string& sequenceFile)
{
	this->closeSequence();
	this->_filePath = sequenceFile;
	this->_sequence->open(this->_filePath);
}

void Level::useRandom(bool random)
{
	this->_random = random;
}

LevelFactoryInitializer::LevelFactoryInitializer()
{
	LevelFactory::_factories[0] = std::make_unique<Level0::Factory>();
	LevelFactory::_factories[1] = std::make_unique<Level1::Factory>();
	LevelFactory::_factories[2] = std::make_unique<Level2::Factory>();
	LevelFactory::_factories[3] = std::make_unique<Level3::Factory>();
	LevelFactory::_factories[4] = std::make_unique<Level4::Factory>();
}

std::unique_ptr<Level> LevelFactory::createLevel(const int& lev, std::string filePath, Game* gameRef, bool rand, std::shared_ptr<std::ifstream> sin)
{
	if( _factories.find(lev) != _factories.end() )
		return _factories[lev]->create(filePath, gameRef, rand, sin);

	return nullptr;
}

// Level0 Implementation
Level0::Level0(std::string filePath, Game* gameRef, bool rand, std::shared_ptr<std::ifstream> sin)
{
	_level = 0;
	_random = false;
	_filePath = filePath;
	_game = gameRef;

	_sequence = sin;
	if (!_sequence->is_open()) {
		std::cerr << "opening level0 boi\n";
		std::cerr << "opening " << filePath << "\n";
		_sequence->open(filePath);
	}
}

Level0::~Level0()
{
	if (_sequence->is_open())
		_sequence->close();
}

void Level0::useRandom(bool use)
{
	// always using a sequence
}

std::shared_ptr<Block> Level0::getNextBlock(void)
{
	char blockType = ' ';
	while (std::isspace(static_cast<unsigned char>(blockType)) != 0)
		blockType = _sequence->get();

	if (_sequence->eof()) {
		std::cerr << "EOF boi\n";
		return nullptr;
	}
	else {
		return BlockFactory::createBlock(blockType, this->_level);
	}
}

// Returns random character from blocks with uniform probability
char randomBlock(std::string blocks)
{
	return blocks[std::rand() % blocks.size()];
}


// Level1 Implementation
Level1::Level1(std::string filePath, Game* gameRef, bool rand, std::shared_ptr<std::ifstream> sin)
{
	_level = 1;
	_random = rand;
	_filePath = filePath;
	_game = gameRef;
	_sequence = sin;
}

Level1::~Level1()
{
	if (_sequence->is_open())
		_sequence->close();
}

std::shared_ptr<Block> Level1::getNextBlock(void)
{
	char nextBlockType = '.';
	switch (std::rand()%6)
	{
		// case 0 with probability 1/6
		case 0:
			// randomBlock returns S or Z with uniform probability (1/2)
			// Pr('S') = Pr('Z') = Pr(case 0) * 1/2 = 1/6 * 1/2 = 1/12
			nextBlockType = randomBlock(std::string("SZ"));
			break;

		// default with probability 5/6
		default:
			// randomBlock returns one of IJLOT with uniform probability (1/5)
			// Pr(any of IJLOT) = Pr(default) * 1/5 = 5/6 * 1/5 = 1/6
			nextBlockType = randomBlock(std::string("IJLOT"));
			break;

	}
	return BlockFactory::createBlock(nextBlockType, this->_level);
}


// Level2 Implementation
Level2::Level2(std::string filePath, Game* gameRef, bool rand, std::shared_ptr<std::ifstream> sin)
{
	_level = 2;
	_random = rand;
	_filePath = filePath;
	_game = gameRef;
	_sequence = sin;
}

Level2::~Level2()
{
	if (_sequence->is_open())
		_sequence->close();
}

std::shared_ptr<Block> Level2::getNextBlock(void)
{
	// Any of IJLOSZT with uniform probability (1/7)
	char nextBlockType = randomBlock(std::string("IJLOSZT"));
	return BlockFactory::createBlock(nextBlockType, this->_level);
}


// Level3 Implementation
Level3::Level3(std::string filePath, Game* gameRef, bool rand, std::shared_ptr<std::ifstream> sin)
{
	_level = 3;
	_random = rand;
	_filePath = filePath;
	_game = gameRef;

	_sequence = sin;
	assert(rand == !sin->is_open());

	if (!rand && !sin->is_open())
		_sequence->open(filePath);
}

Level3::~Level3()
{
	if (_sequence->is_open())
		_sequence->close();
}

std::shared_ptr<Block> Level3::getNextBlock(void)
{
	char nextBlockType = '.';
	switch (std::rand() % 9)
	{
		case 0:
		case 1:
		case 2:
		case 3:
			nextBlockType = randomBlock(std::string("SZ"));
			break;
		default:
			nextBlockType = randomBlock(std::string("IJLOT"));
			break;
	}
	return BlockFactory::createBlock(nextBlockType, this->_level);
}


// Level4 Implementation
Level4::Level4(std::string filePath, Game* gameRef, bool rand, std::shared_ptr<std::ifstream> sin)
{
	_level = 4;
	_random = rand;
	_filePath = filePath;
	_game = gameRef;

	_level3 = Level3(filePath, gameRef, rand, sin);

	_sequence = sin;
	assert(rand == !sin->is_open());

	if (!rand && !sin->is_open())
		_sequence->open(filePath);
}

Level4::~Level4()
{
	if (_sequence->is_open())
		_sequence->close();
}

std::shared_ptr<Block> Level4::getNextBlock(void)
{
	int bsc = this->_game->getNumBlocksSinceClear();
	if (bsc % 5 == 0 && bsc != 0)
		return BlockFactory::createBlock('D', this->_level);

	return this->_level3.getNextBlock();
}
