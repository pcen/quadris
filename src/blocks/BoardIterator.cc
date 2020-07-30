#include "BoardIterator.h"

Cell BoardIterator::operator*() const
{
	return *this->_cells[_x][_y];
}

BoardIterator& BoardIterator::operator++()
{
	_x++;
	if (_x >= _cols) {
		_y--;
		if (_y >= 0)
			_x = 0;
	}

	return *this;
}

bool BoardIterator::operator!=(const BoardIterator& other) const
{
	return _cells != other._cells || _x != other._x || _y != other._y;
}
