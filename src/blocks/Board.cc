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

bool Board::_validTranslation(std::shared_ptr<Block> block, Direction direction)
{
	// coordinate offsets of translation
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
	auto cells = block->getCells();
	for (auto& c : cells) {
		Coord newPos(c->get_x() + dx, c->get_y() + dy);
		// if the new position is out of bounds, return false
		if (!this->_inBounds(newPos))
			return false;

		// if the new position is not empty cells, return false
		if (this->at(newPos).getType() != BlockType::EMPTY)
			return false;
	}
	return true;
}

void Board::_insertBlock(std::shared_ptr<Block> block)
{
	auto cells = block->getCells();
	for (auto& c : cells)
		this->_board[c->get_x()][c->get_y()] = c;
}

// gameplay methods

bool Board::moveY(bool isDrop)
{
	if (this->_validTranslation(this->_currentBlock, Direction::DOWN))
		return true;
	return false;
}

bool Board::setCurrentBlock(std::shared_ptr<Block> currentBlock)
{
	this->_currentBlock = currentBlock;
	return true;
	// if (!this->_validTranslation(currentBlock, Direction::NONE));
	// 	return false;
	// this->_insertBlock(currentBlock);
	// return true;
}
