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
	GraphicsView gv("Quadris", &game);

	std::string flag1;
	if (argc > 1)
		flag1 = argv[1];
	else
		flag1 = "\0";

	auto thread1 = cv.start();
	auto thread2 = gv.start();

	return 0;
}
