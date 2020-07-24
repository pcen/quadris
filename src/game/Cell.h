#ifndef CELL_H
#define CELL_H

#include "../graphics/Sprite2D.h"

class Cell
{
public:
	Cell();
	Sprite2D getSprite(void);
private:
	Sprite2D _sprite;
};

#endif // CELL_H
