#ifndef BLOCK_H
#define BLOCK_H

#include "Cell.h"

#include <vector>
#include <memory>

enum class BlockType : char {
	I = 'I',
	J = 'J',
	L = 'L',
	O = 'O',
	S = 'S',
	Z = 'Z',
	T = 'T',
	EMPTY = '.'
};

class Block
{
public:

	virtual void _rotate(bool) = 0;

	virtual bool moveX(bool);
	virtual bool moveY(bool);

	BlockType getType(void);

private:

	BlockType _type;
	std::vector<std::shared_ptr<Cell>> _cells;
	Coord _bottomLeft;

	int _levelGenerated;
	bool _isHeavy;

};

#endif // BLOCK_H
