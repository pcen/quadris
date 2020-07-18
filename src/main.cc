#include <iostream>
#include <future>

#include "window/X11Window.h"
#include "views/ConsoleView.h"
#include "views/GraphicsView.h"
#include "game/Game.h"

int main(int argc, char* argv[])
{
	Game game;
	ConsoleView cv(std::cin, &game);
	GraphicsView gv(&game);

	std::string flag1;
	if (argc > 1)
		flag1 = argv[1];
	else
		flag1 = "\0";

	auto thread1 = cv.start();

	X11Window window("Quadris");
	// TODO: window should be notified when game is done running,
	// currently window will remain open even when game quits
	window.start();

	return 0;
}
