#ifndef BOARD_H
#define BOARD_H

#include "BoardIterator.h"
#include "Block.h"
#include "../graphics/Sprite2D.h"

#include <vector>

float constexpr default_cell_size = 25.0f;

class Window;
class ConsoleView;

class Board
{
	friend class Window;
	friend class ConsoleView;

public:
	Board();
	Board(std::string png, float cell_size = default_cell_size);

	float get_cell_size(void) const;

private:

	float _cell_size;

	std::vector<std::vector<std::shared_ptr<Cell>>> _board;
	std::vector<std::shared_ptr<Block>> _blocks;
	std::shared_ptr<Block> _currentBlock;
	std::vector<int> _topOfColumns;
	int _numBlockSinceClear;

	BoardIterator begin() const;
	BoardIterator end() const;

};

#endif // BOARD_H
