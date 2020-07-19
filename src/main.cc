#include <iostream>
#include <thread>

#include "views/ConsoleView.h"
#include "views/GraphicsView.h"
#include "game/Game.h"
#include "controller/CommandInterpreter.h"

int main(int argc, char* argv[])
{
	Game game;
	CommandInterpreter controller(&game);

	ConsoleView cv(&game, &controller, std::cin);

	while (game.is_running()) {
		if (!controller.empty())
			controller.flush_commands();
	}
	return 0;
}
