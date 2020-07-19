#include <iostream>

#include "views/ConsoleView.h"
#include "views/GraphicsView.h"
#include "views/ViewManager.h"
#include "game/Game.h"
#include "controller/CommandInterpreter.h"

int main(int argc, char* argv[])
{
	Game game;
	CommandInterpreter cmdint(&game);
	ViewManager views;

	ConsoleView cv(&game, &cmdint, std::cin);
	// TODO: spoof argc/argv with special GraphicsView members
	// qt[argc/argv] since argc and argv should not need to
	// be passed to a GraphicsView constructor
	GraphicsView gv("Quadris", &game, &cmdint, argc, argv);

	views.push(&cv);
	views.push(&gv);

	while (game.is_running()) {
		cmdint.send_commands();
		views.poll_input();
	}
	return 0;
}
