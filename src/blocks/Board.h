#ifndef BOARD_H
#define BOARD_H

#include "BoardIterator.h"
#include "Block.h"

#include <vector>

float constexpr default_cell_size = 25.0f;

class Window;
class ConsoleView;

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

class Board
{
public:
	Board();
	Board(std::string png, float cell_size = default_cell_size);

	Cell at(Coord coord) const;

	float getCellSize(void) const;

	bool moveY(bool isDrop);

	std::shared_ptr<Block> getCurrentBlock(void) const;
	bool setCurrentBlock(std::shared_ptr<Block> currentBlock);

	BoardIterator begin() const;
	BoardIterator end() const;

private:
	friend class Game;

	float _cell_size;
	bool _inBounds(int x, int y);
	bool _inBounds(Coord coord);
	void _insertBlock(std::shared_ptr<Block> block);
	void _doTranslation(Direction direction);
	bool _validTranslation(Direction direction);

	Coord _directionDeltas(Direction direction);

	std::vector<std::vector<std::shared_ptr<Cell>>> _board;
	std::vector<std::shared_ptr<Block>> _blocks;
	std::shared_ptr<Block> _currentBlock;
	std::vector<int> _topOfColumns;
	int _numBlockSinceClear;

};

#endif // BOARD_H
