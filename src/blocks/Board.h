#ifndef BOARD_H
#define BOARD_H

#include "BoardIterator.h"
#include "Block.h"

#include <vector>

#define BOARD_HEIGHT 18
#define BOARD_WIDTH 11

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
	int insertCurrentBlock(void);
	// rotate the current block
	bool rotate(bool clockwise);
	// show hint
	void hint(void);
	// true if hint is being displayed
	bool hasHint(void) const;
	// remove the hint block
	void removeHint(void);

	// set the currently active block
	bool setCurrentBlock(std::shared_ptr<Block> currentBlock);

	// get the currently active block
	std::shared_ptr<Block> getCurrentBlock(void) const;

	// set the next block
	void setNextBlock(std::shared_ptr<Block> nextBlock);

	// get the next block
	std::shared_ptr<Block> getNextBlock(void) const;

	// get the hint block
	std::shared_ptr<Block> getHintBlock(void) const;

	std::vector<std::shared_ptr<Block>>& getBlocks(void);

	BoardIterator begin(void) const;
	BoardIterator end(void) const;

private:
	friend class Game;

	float _cellSize;

	void _insertBlock(std::shared_ptr<Block> block);
	int _clearRows(void);

	// row filled helpers
	void _clearSingleRow(int row);
	void _shiftDown(int bottom, int highest, int offset);
	bool _isRowEmpty(int row);
	bool _isRowFull(int row);
	void _shiftSingleRowDown(int row, int offset = 1);
	void _clearCell(int x, int y);

	// board boundary checking
	bool _inBounds(int x, int y);
	bool _inBounds(Coord coord);

	// block translation helpers
	void _doTranslation(Direction direction);
	bool _validTranslation(Direction direction);
	Coord _directionDeltas(Direction direction);

	// block rotation helpers
	void _doRotation(bool clockwise);

	// hint helpers
	void _calculateHintPosition(void);

	std::string _emptyCellSprite;
	std::vector<std::vector<std::shared_ptr<Cell>>> _board;
	std::vector<std::shared_ptr<Block>> _blocks;

	std::shared_ptr<Block> _currentBlock;
	std::shared_ptr<Block> _nextBlock;
	std::shared_ptr<Block> _hintBlock;

	int _numBlockSinceClear;
};

#endif // BOARD_H
