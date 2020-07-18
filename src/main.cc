#include <iostream>

#include "views/ConsoleView.h"
#include "views/GraphicsView.h"
#include "game/Game.h"
#include "controller/CommandInterpreter.h"

#include <thread>

int main(int argc, char* argv[])
{
	Game game;
	CommandInterpreter controller(&game);

	std::cerr << "main thread ID: ";
	std::cerr << std::this_thread::get_id() << "\n";

	auto thread1 = ConsoleView::create(&game, &controller);
	auto thread2 = GraphicsView::create("Quadris", &game, &controller);

	while (game.is_running()) {
		if (!controller.empty())
			controller.flush_commands();
	}

	return 0;
}
