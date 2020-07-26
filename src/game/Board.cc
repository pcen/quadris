#include "Board.h"

using namespace std;

Board::Board()
{
	vector< Cell* > nulled(18, nullptr);
	vector<vector< Cell* >> vec(11, nulled);
	_board = vec;

	vector<int> zero(11, 0);
	_topOfColumns = zero;

	_numBlockSinceClear = 0;
}


Board::Board(Sprite2D png)
{
	for (int j = 0; j < 11; ++j) {
		vector< Cell* > images;
		for(int i = 0; i < 18; ++i){
			Cell* newCell = new Cell(png);
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