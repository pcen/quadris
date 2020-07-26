#include "Board.h"

using namespace std;


Board::Board(float cell_size)
	: _cell_size{ cell_size }
{
	vector<int> zero(11, 0);
	this->_topOfColumns = zero;

	this->_numBlockSinceClear = 0;
}

float Board::get_cell_size(void) const
{
	return this->_cell_size;
}

Board::Board(string png, float cell_size)
	: _cell_size{ cell_size }
{
	for (int j = 0; j < 11; ++j) {
		vector<shared_ptr<Cell>> images;
		for(int i = 0; i < 18; ++i){
			shared_ptr<Cell> newCell = make_shared<Cell>(j,i,nullptr,png,false);
			images.push_back(newCell);
		}
		this->_board.push_back(images);
	}
}

BoardIterator Board::begin()
{
	return BoardIterator(0, 0, this->_board[0].size(), this->_board.size(), this->_board);
}

BoardIterator Board::end()
{
	return BoardIterator(this->_board.size(), this->_board[0].size(), this->_board.size(), this->_board[0].size(), this->_board);
}
