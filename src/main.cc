#include <iostream>

#include "views/ConsoleView.h"
#include "views/GraphicsView.h"
#include "views/ViewManager.h"
#include "game/Game.h"
#include "game/Controller.h"

int main(int argc, char* argv[])
{
	Game game;
	Controller ctrl(game);
	ViewManager views;

	ConsoleView cv(&game, &ctrl, std::cin, std::cout);
	// TODO: spoof argc/argv with special GraphicsView members
	// qt[argc/argv] since argc and argv should not need to
	// be passed to a GraphicsView constructor
	GraphicsView gv("Quadris", &game, &ctrl, argc, argv);

	views.push(&cv);
	views.push(&gv);

	while (game.isRunning()) {
		ctrl.send_commands();
		views.pollInput();
	}

	return 0;
}
