#include "StandardLevels.h"


Level0::Level0(std::string filePath, Game* gameRef, bool rand)
{
	_level = 0;
	_random = rand;
	_filePath = filePath;
	_sequence.open(filePath);
	_game = gameRef;
}

std::shared_ptr<Block> Level0::getNextBlock(void) const
{

}


Level1::Level1(std::string filePath, Game* gameRef, bool rand)
{
	_level = 1;
	_random = rand;
	_filePath = filePath;
	_game = gameRef;
}

std::shared_ptr<Block> Level1::getNextBlock(void) const
{

}


Level2::Level2(std::string filePath, Game* gameRef, bool rand)
{
	_level = 2;
	_random = rand;
	_filePath = filePath;
	_game = gameRef;
}

std::shared_ptr<Block> Level2::getNextBlock(void) const
{

}


Level3::Level3(std::string filePath, Game* gameRef, bool rand)
{
	_level = 3;
	_random = rand;
	_filePath = filePath;
	_game = gameRef;
}

std::shared_ptr<Block> Level3::getNextBlock(void) const
{

}


Level4::Level4(std::string filePath, Game* gameRef, bool rand, std::shared_ptr<Level3> lev3) : Level3(filePath, gameRef, rand)
{
	_level = 4;
	_random = rand;
	_filePath = filePath;
	_game = gameRef;
	_level3 = lev3;
}

std::shared_ptr<Block> Level4::getNextBlock(void) const
{

}
