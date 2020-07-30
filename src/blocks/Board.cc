#include "Board.h"

Board::Board()
	: _cell_size{ default_cell_size }
{
	std::vector<int> zero(11, 0);
	this->_topOfColumns = zero;
	this->_numBlockSinceClear = 0;
}

Board::Board(std::string png, float cell_size)
	: _cell_size{ cell_size }
{
	for (int j = 0; j < 11; ++j) {
		std::vector<std::shared_ptr<Cell>> images;
		for(int i = 0; i < 18; ++i){
			std::shared_ptr<Cell> newCell = std::make_shared<Cell>(j, i, nullptr, png, false, (char)BlockType::EMPTY);
			images.push_back(newCell);
		}
		this->_board.push_back(images);
	}
}

float Board::get_cell_size(void) const
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
