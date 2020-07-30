#ifndef CELL_H
#define CELL_H

#include <string>
#include <memory>

class Block;
class Board;

struct Coord
{
	int _x;
	int _y;

	Coord() {};
	Coord(uint x, uint y) : _x(x), _y(y) {};

	Coord invert(void);
};

Coord operator+(Coord a, Coord b);
Coord operator-(Coord a, Coord b);

class Cell
{
public:
	Cell(int x, int y, Block* parent, std::string png, bool isDeleted, char token);

	std::string getSprite(void);
	Coord getCoord(void) const;
	int get_x(void);
	int get_y(void);
	char getToken(void) const;
	const Block* getParent(void) const;

private:
	friend class Board;

	Coord _coords;
	Block* _parent;
	std::string _sprite;
	bool _isDeleted;
	char _token;
};

#endif // CELL_H
