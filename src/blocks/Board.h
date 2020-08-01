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
	void drop(void);
	// insert the currently active block cells into the table
	bool insertCurrentBlock(void);
	// rotate the current block
	bool rotate(bool clockwise);

	// set the currently active block
	bool setCurrentBlock(std::shared_ptr<Block> currentBlock);
	// get the currently active block
	std::shared_ptr<Block> getCurrentBlock(void) const;

	// set the next block
	void setNextBlock(std::shared_ptr<Block> nextBlock);
	// get the next block
	std::shared_ptr<Block> getNextBlock(void) const;

	BoardIterator begin() const;
	BoardIterator end() const;

private:
	friend class Game;

	float _cellSize;

	void _insertBlock(std::shared_ptr<Block> block);

	// board boundary checking
	bool _inBounds(int x, int y);
	bool _inBounds(Coord coord);

	// block translation helpers
	void _doTranslation(Direction direction);
	bool _validTranslation(Direction direction);
	Coord _directionDeltas(Direction direction);

	// block rotation helpers
	void _doRotation(bool clockwise);

	std::string _emptyCellSprite;
	std::vector<std::vector<std::shared_ptr<Cell>>> _board;
	std::vector<std::shared_ptr<Block>> _blocks;

	std::shared_ptr<Block> _currentBlock;
	std::shared_ptr<Block> _nextBlock;

	int _numBlockSinceClear;
};

#endif // BOARD_H
