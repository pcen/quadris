#include <iostream>

#include "window/X11Window.h"
#include "views/ConsoleView.h"
#include "views/GraphicsView.h"
#include "game/Game.h"

int main(int argc, char* argv[])
{
	Game game;

	auto thread1 = ConsoleView::create(&game);
	auto thread2 = GraphicsView::create(&game);

	return 0;
}
