#include "Board.h"

using namespace std;


Cell* BoardIterator::operator*()
{
	return this->_cells[_x][_y];
}


BoardIterator& BoardIterator::operator++()
{
	_x++;
	if (_x >= _cols)
	{
		_y++;
		if (_y < _rows)
			_x = 0;
	}

	return *this;
}


bool BoardIterator::operator!=(const BoardIterator& other)
{
	return _cells != other._cells || _x != other._x || _y != other._y;
}


