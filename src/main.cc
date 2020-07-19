#include <iostream>
#include <thread>

#include "views/ConsoleView.h"
#include "views/GraphicsView.h"
#include "views/ViewManager.h"
#include "game/Game.h"
#include "controller/CommandInterpreter.h"

int main(int argc, char* argv[])
{
	Game game;
	CommandInterpreter controller(&game);
	ViewManager views;

	ConsoleView cv(&game, &controller, std::cin);
	GraphicsView gv("Quardis", &game, &controller, argc, argv);

	views.push(&cv);
	views.push(&gv);

	while (game.is_running()) {
		controller.send_commands();
		views.poll_events();
	}
	return 0;
}
