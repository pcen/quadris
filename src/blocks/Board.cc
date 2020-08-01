#include "Board.h"

#include <iostream>

Board::Board()
	: _cellSize{ default_cell_size }, _numBlockSinceClear{ 0 }
{

}

Board::Board(std::string png, float cellSize)
	: _cellSize{ cellSize }, _emptyCellSprite{ png },
	_currentBlock{ nullptr }, _nextBlock{ nullptr }, _numBlockSinceClear{ 0 }
{
	this->reset();
}

void Board::reset(void)
{
	// clear the board
	for (auto& r : this->_board)
		r.clear();
	this->_board.clear();
	// clear blocks
	this->_blocks.clear();
	// clear the current block
	this->_currentBlock = nullptr;
	// clear the next block
	this->_nextBlock = nullptr;
	// initialize the board to empty cells
	for (int j = 0; j < 11; ++j) {
		std::vector<std::shared_ptr<Cell>> row;
		for(int i = 0; i < 18; ++i){
			auto newCell = std::make_shared<Cell>(j, i, this->_emptyCellSprite, false, BlockType::EMPTY);
			row.push_back(newCell);
		}
		this->_board.push_back(row);
	}
	// reset the number of blocks since last clear count
	this->_numBlockSinceClear = 0;
}

Cell Board::at(Coord coord) const
{
	if (coord._x > 10 || coord._y > 17)
		std::cerr << "invalid coordinates to acces board\n";

	return *this->_board[coord._x][coord._y];
}

std::shared_ptr<Block> Board::getCurrentBlock(void) const
{
	return this->_currentBlock;
}

void Board::setNextBlock(std::shared_ptr<Block> nextBlock)
{
	this ->_nextBlock = nextBlock;
}

std::shared_ptr<Block> Board::getNextBlock(void) const
{
	return this->_nextBlock;
}

std::vector<std::shared_ptr<Block>> Board::getBlocks(void) const 
{
	return _blocks;
}

float Board::getCellSize(void) const
{
	return this->_cellSize;
}

BoardIterator Board::begin() const
{
	return BoardIterator(0, this->_board[0].size() - 1, this->_board[0].size(), this->_board.size(), this->_board);
}

BoardIterator Board::end() const
{
	return BoardIterator(this->_board.size(), -1, this->_board.size(), this->_board[0].size(), this->_board);
}


bool Board::_inBounds(int x, int y)
{
	return 0 <= x && x < 11 && 0 <= y && y < 18;
}

bool Board::_inBounds(Coord coord)
{
	return this->_inBounds(coord._x, coord._y);
}

Coord Board::_directionDeltas(Direction direction)
{
	int dx = 0;
	int dy = 0;
	switch (direction) {
		case Direction::UP:
			dy = 1;
			break;
		case Direction::DOWN:
			dy = -1;
			break;
		case Direction::LEFT:
			dx = -1;
			break;
		case Direction::RIGHT:
			dx = 1;
			break;
		case Direction::NONE:
		default:
			break;
	}
	return Coord(dx, dy);
}

bool Board::_validTranslation(Direction direction)
{
	Coord delta = this->_directionDeltas(direction);
	auto cells = this->_currentBlock->getCells();
	for (auto& c : cells) {
		Coord newPos = c->_coords + delta;
		// if the new position is out of bounds, return false
		if (!this->_inBounds(newPos)) {
			// std::cerr << "not in bounds\n";
			return false;
		}

		// if the new position is not empty cells, return false
		if (this->at(newPos).getType() != BlockType::EMPTY) {
			// std::cerr << "not empty block\n";
			return false;
		}
	}
	return true;
}

void Board::_doTranslation(Direction direction)
{
	Coord delta = this->_directionDeltas(direction);
	this->_currentBlock->_bottomLeft += delta;
	auto cells = this->_currentBlock->getCells();
	for (auto& c : cells) {
		c->_coords += delta;
	}
}

// insert the given block's cells into the board
// this method does not check if the board is currently occupied
// at the blocks position
void Board::_insertBlock(std::shared_ptr<Block> block)
{
	auto cells = block->getCells();
	for (auto& c : cells)
		this->_board[c->get_x()][c->get_y()] = c;
}

// translate the currently active block in the given direction
// translates by 1 cell in the direction specified
bool Board::translate(Direction direction)
{
	if (this->_validTranslation(direction)) {
		this->_doTranslation(direction);
		return true;
	}
	return false;
}

// translate the current block down until it is no longer a valid translation
void Board::drop(void)
{
	while (this->_validTranslation(Direction::DOWN))
		this->_doTranslation(Direction::DOWN);
}

bool Board::rotate(bool clockwise)
{
	// rotate in the given direction
	this->_doRotation(clockwise);

	// check if the resulting position is valid
	if (this->_validTranslation(Direction::NONE)) {
		// rotation was valid
		return true;
	} else {
		// rotation was invalid, so undo rotation
		this->_doRotation(!clockwise);
		return false;
	}
}

void Board::_doRotation(bool clockwise)
{
	// convert the current block coordinates to block space
	this->_currentBlock->blockSpace(true);
	// perform rotation
	if (clockwise) {
		this->_currentBlock->reflectInYeqX();
		this->_currentBlock->flipX();
	} else {
		this->_currentBlock->flipX();
		this->_currentBlock->reflectInYeqX();
	}
	// convert current block back to board space
	this->_currentBlock->blockSpace(false);
}

void Board::_resetRow(unsigned int row) {
	for (unsigned int x = 0; x < 11; x++) {
		auto newCell = std::make_shared<Cell>(x, row, this->_emptyCellSprite, false, BlockType::EMPTY);
		_board[x][row] = newCell;
	}
}

int Board::_clearRows(void)
{
	Block* block = this->_currentBlock.get();
	Coord start = block->_bottomLeft;
	int rowsCleared = 0;

	for (int y = start._y; y < start._y + 4; y++) {
		bool isFilled = true;
		for (int x = 0; x < 11; x++) {
			Cell* c = this->_board[x][y].get();
			if (c->getType() == BlockType::EMPTY) {
				isFilled = false;
				break;
			}
		}
		if (!isFilled)
			break;

		rowsCleared++;
		this->_resetRow(y);
	}

	return rowsCleared;
}

// insert the cells of the currently active block into the board
int Board::insertCurrentBlock(void)
{
	if (this->_validTranslation(Direction::NONE)) {
		// insert the current block's cells into the board
		this->_insertBlock(this->_currentBlock);
		// put the current block into the vector of blocks,
		// since a new block should become current
		this->_blocks.push_back(this->_currentBlock);
		return this->_clearRows();
	}
	else {
		std::cerr << "ERROR: cannot insert current block since it is"
		          << " at an invalid board position.\n";
		return -1;
	}
}

bool Board::setCurrentBlock(std::shared_ptr<Block> currentBlock)
{
	this->_currentBlock = currentBlock;

	// on recieving a nullptr, a level sequence file has reached
	// EOF, and the game is over
	if (currentBlock == nullptr)
		return false;

	if (this->_validTranslation(Direction::NONE))
		return true;
	this->_currentBlock = nullptr;
	return false;
}
