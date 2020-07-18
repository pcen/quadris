#ifndef GAME_H
#define GAME_H

#include <string>

#include "Board.h"

#include "../window/X11Window.h"
class X11Window;

class Game
{

public:
	Game();
	void update(const std::string& command);
	bool is_running(void) const;

private:
	bool _running;
};

#endif // GAME_H
