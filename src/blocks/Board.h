#ifndef BOARD_H
#define BOARD_H

#include "BoardIterator.h"
#include "Cell.h"
#include "Block.h"
#include "../graphics/Sprite2D.h"

#include <vector>

class Window;

class Board
{
	friend class Window;
public:
	Board(float cell_size = 30.0f);
	Board(std::string, float cell_size = 30.0f);

	float get_cell_size(void) const;

private:

	float _cell_size;

	std::vector<std::vector<std::shared_ptr<Cell>>> _board;
	std::vector<std::shared_ptr<Block>> _blocks;
	std::shared_ptr<Block> _currentBlock;
	std::vector<int> _topOfColumns;
	int _numBlockSinceClear;

	BoardIterator begin();
	BoardIterator end();

};

#endif // BOARD_H
