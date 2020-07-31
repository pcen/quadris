#include <assert.h>
#include <iostream>

#include "StandardLevels.h"

// define static instances
std::map<int, std::unique_ptr<LevelFactory>> LevelFactory::_factories;
LevelFactoryInitializer LevelFactoryInitializer::lfi;

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


Level0::Level0(std::string filePath, Game* gameRef, bool rand, std::shared_ptr<std::ifstream> sin)
{
	_level = 0;
	_random = rand;
	_filePath = filePath;
	_game = gameRef;

	_sequence = sin;
	if (!_sequence->is_open())
		_sequence->open(filePath);
}

Level0::~Level0()
{
	if (_sequence->is_open())
		_sequence->close();
}

std::shared_ptr<Block> Level0::getNextBlock(void)
{
	char blockType = ' ';
	while (std::isspace(static_cast<unsigned char>(blockType)) != 0)
		blockType = _sequence->get();

	if (_sequence->eof())
		return nullptr;
	else
		return BlockFactory::createBlock(blockType, _level);
}




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

}




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

}




Level3::Level3(std::string filePath, Game* gameRef, bool rand, std::shared_ptr<std::ifstream> sin)
{
	_level = 3;
	_random = rand;
	_filePath = filePath;
	_game = gameRef;

	_sequence = sin;
	assert(rand == sin->is_open());

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

}




Level4::Level4(std::string filePath, Game* gameRef, bool rand, std::shared_ptr<std::ifstream> sin)
{
	_level = 4;
	_random = rand;
	_filePath = filePath;
	_game = gameRef;

	_level3 = Level3(filePath, gameRef, rand, sin);

	_sequence = sin;
	assert(rand == sin->is_open());

	if (!rand && !sin->is_open());
		_sequence->open(filePath);
}

Level4::~Level4()
{
	if (_sequence->is_open())
		_sequence->close();
}

std::shared_ptr<Block> Level4::getNextBlock(void)
{

}
