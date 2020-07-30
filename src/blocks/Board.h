#ifndef BOARD_H
#define BOARD_H

#include "BoardIterator.h"
#include "Block.h"

#include <vector>

float constexpr default_cell_size = 25.0f;

class Window;
class ConsoleView;

class Board
{
public:
	Board();
	Board(std::string png, float cell_size = default_cell_size);

	Cell at(Coord& coord) const;

	float getCellSize(void) const;

	bool moveY(bool isDrop);

	void setCurrentBlock(std::shared_ptr<Block> currentBlock);

	BoardIterator begin() const;
	BoardIterator end() const;

private:
	friend class Game;

	float _cell_size;

	std::vector<std::vector<std::shared_ptr<Cell>>> _board;
	std::vector<std::shared_ptr<Block>> _blocks;
	std::shared_ptr<Block> _currentBlock;
	std::vector<int> _topOfColumns;
	int _numBlockSinceClear;

};

#endif // BOARD_H
