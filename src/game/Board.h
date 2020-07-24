#ifndef BOARD_H
#define BOARD_H

#include "Cell.h"

#include <vector>

class Board
{
public:
	Board();

	std::vector<std::vector<Sprite2D>> _board;
private:

};

#endif // BOARD_H
