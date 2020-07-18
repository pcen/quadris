#include <iostream>

#include "window/X11Window.h"
#include "views/ConsoleView.h"
#include "views/GraphicsView.h"
#include "game/Game.h"

#include <thread>

int main(int argc, char* argv[])
{
	Game game;

	std::cerr << "main thread ID: ";
	std::cerr << std::this_thread::get_id() << "\n";

	auto thread1 = ConsoleView::create(&game);
	auto thread2 = GraphicsView::create("Quadris", &game);

	return 0;
}
