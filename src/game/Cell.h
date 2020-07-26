#ifndef CELL_H
#define CELL_H

#include "../graphics/Sprite2D.h"

class Cell
{
public:
	Cell();
	Cell(Sprite2D png) {
		_sprite = png;
	};
	Sprite2D getSprite(void) {
		return _sprite;
	};
private:
	Sprite2D _sprite;
};

#endif // CELL_H
