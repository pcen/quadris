#include "Board.h"

using namespace std;


Board::Board()
{
	vector<int> zero(11, 0);
	_topOfColumns = zero;

	_numBlockSinceClear = 0;
}


Board::Board(Sprite2D png)
{
	for (int j = 0; j < 11; ++j) {
		vector<shared_ptr<Cell>> images;
		for(int i = 0; i < 18; ++i){
			shared_ptr<Cell> newCell = make_shared<Cell>(png);
			images.push_back(newCell);
		}
		_board.push_back(images);
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