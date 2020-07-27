#include "Cell.h"

using namespace std;

Cell::Cell(int x, int y, std::shared_ptr<Block> parent, string png, bool isDeleted, char token)
	: _coords{x, y}, _parent{parent}, _sprite{Sprite2D(png)}, _isDeleted{isDeleted}, _token{ token }
{

}

Sprite2D Cell::getSprite(void)
{
	return _sprite;
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
