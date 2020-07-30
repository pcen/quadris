#ifndef CELL_H
#define CELL_H

#include "../graphics/Sprite2D.h"

#include <string>

class Block;

struct Coord
{
	int _x;
	int _y;

	Coord invert(void);

	Coord() {};
	Coord(uint x, uint y) : _x(x), _y(y) {};
};

Coord operator+(Coord a, Coord b);
Coord operator-(Coord a, Coord b);

class Cell
{
public:
	Cell(int x, int y, std::shared_ptr<Block> parent, std::string png, bool isDeleted, char token);

	std::string getSprite(void);
	int get_x(void);
	int get_y(void);
	char getToken(void) const;

private:
	Coord _coords;
	std::shared_ptr<Block> _parent;
	std::string _sprite;
	bool _isDeleted;
	char _token;
};

#endif // CELL_H
