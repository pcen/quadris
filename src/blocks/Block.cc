#include "Block.h"
#include "StandardBlocks.h"

using namespace std;


BlockFactoryInitializer::BlockFactoryInitializer()
{
	BlockFactory::_factories["I"] = make_unique<IBlock::Factory>();
	BlockFactory::_factories["J"] = make_unique<JBlock::Factory>();
	BlockFactory::_factories["L"] = make_unique<LBlock::Factory>();
	BlockFactory::_factories["O"] = make_unique<OBlock::Factory>();
	BlockFactory::_factories["S"] = make_unique<SBlock::Factory>();
	BlockFactory::_factories["Z"] = make_unique<ZBlock::Factory>();
	BlockFactory::_factories["T"] = make_unique<TBlock::Factory>();
}


shared_ptr<Block> BlockFactory::createBlock(const string& id, int level)
{
	if( _factories.find(id) != _factories.end() )
		return _factories[id] -> create(level);
}


IBlock::IBlock(int level)
{
	_type = BlockType::I;
	_bottomLeft = Coord(0,14);

	_cells.emplace_back(make_shared<Cell>(0,14,shared_from_this(),"./assets/i.png",false));
	_cells.emplace_back(make_shared<Cell>(1,14,shared_from_this(),"./assets/i.png",false));
	_cells.emplace_back(make_shared<Cell>(2,14,shared_from_this(),"./assets/i.png",false));
	_cells.emplace_back(make_shared<Cell>(3,14,shared_from_this(),"./assets/i.png",false));

	_levelGenerated = level;
	_isHeavy = (_levelGenerated >= 3);
}


JBlock::JBlock(int level)
{
	_type = BlockType::J;
	_bottomLeft = Coord(0,13);

	_cells.emplace_back(make_shared<Cell>(0,14,shared_from_this(),"./assets/j.png",false));
	_cells.emplace_back(make_shared<Cell>(0,13,shared_from_this(),"./assets/j.png",false));
	_cells.emplace_back(make_shared<Cell>(1,13,shared_from_this(),"./assets/j.png",false));
	_cells.emplace_back(make_shared<Cell>(2,13,shared_from_this(),"./assets/j.png",false));

	_levelGenerated = level;
	_isHeavy = (_levelGenerated >= 3);
}


LBlock::LBlock(int level)
{
	_type = BlockType::L;
	_bottomLeft = Coord(0,13);

	_cells.emplace_back(make_shared<Cell>(0,13,shared_from_this(),"./assets/l.png",false));
	_cells.emplace_back(make_shared<Cell>(1,13,shared_from_this(),"./assets/l.png",false));
	_cells.emplace_back(make_shared<Cell>(2,13,shared_from_this(),"./assets/l.png",false));
	_cells.emplace_back(make_shared<Cell>(2,14,shared_from_this(),"./assets/l.png",false));

	_levelGenerated = level;
	_isHeavy = (_levelGenerated >= 3);
}


OBlock::OBlock(int level)
{
	_type = BlockType::O;
	_bottomLeft = Coord(0,13);

	_cells.emplace_back(make_shared<Cell>(0,13,shared_from_this(),"./assets/o.png",false));
	_cells.emplace_back(make_shared<Cell>(0,14,shared_from_this(),"./assets/o.png",false));
	_cells.emplace_back(make_shared<Cell>(1,13,shared_from_this(),"./assets/o.png",false));
	_cells.emplace_back(make_shared<Cell>(1,14,shared_from_this(),"./assets/o.png",false));

	_levelGenerated = level;
	_isHeavy = (_levelGenerated >= 3);
}


SBlock::SBlock(int level)
{
	_type = BlockType::S;
	_bottomLeft = Coord(0,13);

	_cells.emplace_back(make_shared<Cell>(0,13,shared_from_this(),"./assets/s.png",false));
	_cells.emplace_back(make_shared<Cell>(1,13,shared_from_this(),"./assets/s.png",false));
	_cells.emplace_back(make_shared<Cell>(1,14,shared_from_this(),"./assets/s.png",false));
	_cells.emplace_back(make_shared<Cell>(2,14,shared_from_this(),"./assets/s.png",false));

	_levelGenerated = level;
	_isHeavy = (_levelGenerated >= 3);
}


ZBlock::ZBlock(int level)
{
	_type = BlockType::Z;
	_bottomLeft = Coord(0,13);

	_cells.emplace_back(make_shared<Cell>(0,14,shared_from_this(),"./assets/z.png",false));
	_cells.emplace_back(make_shared<Cell>(1,14,shared_from_this(),"./assets/z.png",false));
	_cells.emplace_back(make_shared<Cell>(1,13,shared_from_this(),"./assets/z.png",false));
	_cells.emplace_back(make_shared<Cell>(2,13,shared_from_this(),"./assets/z.png",false));

	_levelGenerated = level;
	_isHeavy = (_levelGenerated >= 3);
}


TBlock::TBlock(int level)
{
	_type = BlockType::T;
	_bottomLeft = Coord(0,13);

	_cells.emplace_back(make_shared<Cell>(0,14,shared_from_this(),"./assets/t.png",false));
	_cells.emplace_back(make_shared<Cell>(1,14,shared_from_this(),"./assets/t.png",false));
	_cells.emplace_back(make_shared<Cell>(1,13,shared_from_this(),"./assets/t.png",false));
	_cells.emplace_back(make_shared<Cell>(2,14,shared_from_this(),"./assets/t.png",false));

	_levelGenerated = level;
	_isHeavy = (_levelGenerated >= 3);
}


BlockType Block::getType(void)
{
	return this->_type;
}