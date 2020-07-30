#include "Cell.h"

Coord operator+(Coord a, Coord b)
{
	return Coord(a._x + b._x, a._y + b._y);
}

Coord operator-(Coord a, Coord b)
{
	return Coord(a._x - b._x, a._y - b._y);
}

Coord Coord::invert(void)
{
	return Coord(this->_y, this->_x);
}

Cell::Cell(int x, int y, Block* parent, std::string png, bool isDeleted, char token)
	: _coords{x, y}, _parent{parent}, _sprite{png}, _isDeleted{isDeleted}, _token{ token }
{

}

std::string Cell::getSprite(void)
{
	return _sprite;
}

Coord Cell::getCoord(void) const
{
	return this->_coords;
}

int Cell::get_x(void)
{
	return this->_coords._x;
}

int Cell::get_y(void)
{
	return this->_coords._y;
}

char Cell::getToken(void) const
{
	return this->_token;
}

const Block* Cell::getParent(void) const
{
	return this->_parent;
}
