#include "Block.h"
#include "StandardBlocks.h"

// Coord Implementation =======================================================
Coord operator+(Coord a, Coord b)
{
	return Coord(a._x + b._x, a._y + b._y);
}

Coord operator-(Coord a, Coord b)
{
	return Coord(a._x - b._x, a._y - b._y);
}

Coord Coord::invert(void)
{
	return Coord(this->_y, this->_x);
}

// Cell Implementation ========================================================
Cell::Cell(int x, int y, std::string png, bool isDeleted, BlockType type)
	: _coords{x, y}, _type{type}, _sprite{png}, _isDeleted{isDeleted}
{

}

std::string Cell::getSprite(void)
{
	return _sprite;
}

Coord Cell::getCoord(void) const
{
	return this->_coords;
}

int Cell::get_x(void)
{
	return this->_coords._x;
}

int Cell::get_y(void)
{
	return this->_coords._y;
}

char Cell::getToken(void) const
{
	return (char)this->_type;
}

BlockType Cell::getType(void) const
{
	return this->_type;
}

// define static instances
std::map<char, std::unique_ptr<BlockFactory>> BlockFactory::_factories;
BlockFactoryInitializer BlockFactoryInitializer::bfi;

BlockFactoryInitializer::BlockFactoryInitializer()
{
	BlockFactory::_factories['I'] = std::make_unique<IBlock::Factory>();
	BlockFactory::_factories['J'] = std::make_unique<JBlock::Factory>();
	BlockFactory::_factories['L'] = std::make_unique<LBlock::Factory>();
	BlockFactory::_factories['O'] = std::make_unique<OBlock::Factory>();
	BlockFactory::_factories['S'] = std::make_unique<SBlock::Factory>();
	BlockFactory::_factories['Z'] = std::make_unique<ZBlock::Factory>();
	BlockFactory::_factories['T'] = std::make_unique<TBlock::Factory>();
}

std::shared_ptr<Block> BlockFactory::createBlock(const char& id, int level)
{
	if( _factories.find(id) != _factories.end() )
		return _factories[id]->create(level);
	
	return nullptr;
}

// Block Constructors =========================================================
IBlock::IBlock(int level)
{
	_type = BlockType::I;
	_bottomLeft = Coord(0,14);

	_cells.emplace_back(std::make_shared<Cell>(0,14,"./assets/t.png",false,BlockType::I));
	_cells.emplace_back(std::make_shared<Cell>(1,14,"./assets/t.png",false,BlockType::I));
	_cells.emplace_back(std::make_shared<Cell>(2,14,"./assets/t.png",false,BlockType::I));
	_cells.emplace_back(std::make_shared<Cell>(3,14,"./assets/t.png",false,BlockType::I));

	_levelGenerated = level;
	_isHeavy = (level >= 3);
}

JBlock::JBlock(int level)
{
	_type = BlockType::J;
	_bottomLeft = Coord(0,13);

	_cells.emplace_back(std::make_shared<Cell>(0,14,"./assets/n.png",false,BlockType::J));
	_cells.emplace_back(std::make_shared<Cell>(0,13,"./assets/n.png",false,BlockType::J));
	_cells.emplace_back(std::make_shared<Cell>(1,13,"./assets/n.png",false,BlockType::J));
	_cells.emplace_back(std::make_shared<Cell>(2,13,"./assets/n.png",false,BlockType::J));

	_levelGenerated = level;
	_isHeavy = (level >= 3);
}

LBlock::LBlock(int level)
{
	_type = BlockType::L;
	_bottomLeft = Coord(0,13);

	_cells.emplace_back(std::make_shared<Cell>(0,13,"./assets/b.png",false,BlockType::L));
	_cells.emplace_back(std::make_shared<Cell>(1,13,"./assets/b.png",false,BlockType::L));
	_cells.emplace_back(std::make_shared<Cell>(2,13,"./assets/b.png",false,BlockType::L));
	_cells.emplace_back(std::make_shared<Cell>(2,14,"./assets/b.png",false,BlockType::L));

	_levelGenerated = level;
	_isHeavy = (level >= 3);
}

OBlock::OBlock(int level)
{
	_type = BlockType::O;
	_bottomLeft = Coord(0,13);

	_cells.emplace_back(std::make_shared<Cell>(0,13,"./assets/y.png",false,BlockType::O));
	_cells.emplace_back(std::make_shared<Cell>(0,14,"./assets/y.png",false,BlockType::O));
	_cells.emplace_back(std::make_shared<Cell>(1,13,"./assets/y.png",false,BlockType::O));
	_cells.emplace_back(std::make_shared<Cell>(1,14,"./assets/y.png",false,BlockType::O));

	_levelGenerated = level;
	_isHeavy = (level >= 3);
}

SBlock::SBlock(int level)
{
	_type = BlockType::S;
	_bottomLeft = Coord(0,13);

	_cells.emplace_back(std::make_shared<Cell>(0,13,"./assets/g.png",false,BlockType::S));
	_cells.emplace_back(std::make_shared<Cell>(1,13,"./assets/g.png",false,BlockType::S));
	_cells.emplace_back(std::make_shared<Cell>(1,14,"./assets/g.png",false,BlockType::S));
	_cells.emplace_back(std::make_shared<Cell>(2,14,"./assets/g.png",false,BlockType::S));

	_levelGenerated = level;
	_isHeavy = (level >= 3);
}

ZBlock::ZBlock(int level)
{
	_type = BlockType::Z;
	_bottomLeft = Coord(0,13);

	_cells.emplace_back(std::make_shared<Cell>(0,14,"./assets/r.png",false,BlockType::Z));
	_cells.emplace_back(std::make_shared<Cell>(1,14,"./assets/r.png",false,BlockType::Z));
	_cells.emplace_back(std::make_shared<Cell>(1,13,"./assets/r.png",false,BlockType::Z));
	_cells.emplace_back(std::make_shared<Cell>(2,13,"./assets/r.png",false,BlockType::Z));

	_levelGenerated = level;
	_isHeavy = (level >= 3);
}

TBlock::TBlock(int level)
{
	_type = BlockType::T;
	_bottomLeft = Coord(0,13);

	_cells.emplace_back(std::make_shared<Cell>(0,14,"./assets/p.png",false,BlockType::T));
	_cells.emplace_back(std::make_shared<Cell>(1,14,"./assets/p.png",false,BlockType::T));
	_cells.emplace_back(std::make_shared<Cell>(1,13,"./assets/p.png",false,BlockType::T));
	_cells.emplace_back(std::make_shared<Cell>(2,14,"./assets/p.png",false,BlockType::T));

	_levelGenerated = level;
	_isHeavy = (level >= 3);
}


// Block Methods
BlockType Block::getType(void)
{
	return this->_type;
}

std::vector<std::shared_ptr<Cell>>& Block::getCells(void)
{
	return this->_cells;
}
