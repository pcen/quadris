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
	Board(std::string png, float cellSize = default_cell_size);

	Cell at(Coord coord) const;

	float getCellSize(void) const;

	// clears all cells and the block vector
	void reset(void);

	// translate the currently active block in the given direction
	bool translate(Direction direction);
	// drop the currently active block
	bool drop(void);
	// insert the currently active block cells into the table
	bool insertCurrentBlock(void);

	// set the currently active block
	bool setCurrentBlock(std::shared_ptr<Block> currentBlock);
	// get the currently active block
	std::shared_ptr<Block> getCurrentBlock(void) const;

	BoardIterator begin() const;
	BoardIterator end() const;

private:
	friend class Game;

	float _cellSize;
	bool _inBounds(int x, int y);
	bool _inBounds(Coord coord);
	void _insertBlock(std::shared_ptr<Block> block);
	void _doTranslation(Direction direction);
	bool _validTranslation(Direction direction);

	Coord _directionDeltas(Direction direction);

	std::string _emptyCellSprite;
	std::vector<std::vector<std::shared_ptr<Cell>>> _board;
	std::vector<std::shared_ptr<Block>> _blocks;
	std::shared_ptr<Block> _currentBlock;
	std::vector<int> _topOfColumns;
	int _numBlockSinceClear;
};

#endif // BOARD_H
