#include "Board.h"

#include <iostream>

Board::Board()
	: _cell_size{ default_cell_size }
{
	std::vector<int> zero(11, 0);
	this->_topOfColumns = zero;
	this->_numBlockSinceClear = 0;
}

Board::Board(std::string png, float cell_size)
	: _cell_size{ cell_size }, _currentBlock{ nullptr }
{
	for (int j = 0; j < 11; ++j) {
		std::vector<std::shared_ptr<Cell>> images;
		for(int i = 0; i < 18; ++i){
			std::shared_ptr<Cell> newCell = std::make_shared<Cell>(j, i, png, false, BlockType::EMPTY);
			images.push_back(newCell);
		}
		this->_board.push_back(images);
	}
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

float Board::getCellSize(void) const
{
	return this->_cell_size;
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
		Coord newPos(c->get_x() + delta._x, c->get_y() + delta._y);
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
	std::cerr << "true!\n";
	return true;
}

void Board::_doTranslation(Direction direction)
{
	Coord delta = this->_directionDeltas(direction);
	auto cells = this->_currentBlock->getCells();
	for (auto& c : cells) {
		c->_coords._x += delta._x;
		c->_coords._y += delta._y;
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
bool Board::drop(void)
{
	bool dropped = false;
	while (this->_validTranslation(Direction::DOWN)) {
		dropped = true;
		this->_doTranslation(Direction::DOWN);
	}
	return dropped;
}

// insert the cells of the currently active block into the board
bool Board::insertCurrentBlock(void)
{
	if (this->_validTranslation(Direction::NONE)) {
		// insert the current block's cells into the board
		this->_insertBlock(this->_currentBlock);
		// put the current block into the vector of blocks,
		// since a new block should become current
		this->_blocks.push_back(this->_currentBlock);
		return true;
	}
	else {
		std::cerr << "ERROR: cannot insert current block since it is"
		          << " at an invalid board position.\n";
		return false;
	}
}

bool Board::setCurrentBlock(std::shared_ptr<Block> currentBlock)
{
	this->_currentBlock = currentBlock;
	if (this->_validTranslation(Direction::NONE))
		return true;
	this->_currentBlock = nullptr;
	return false;
}
