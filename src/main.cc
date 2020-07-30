#include <iostream>

#include "views/ConsoleView.h"
#include "views/GraphicsView.h"
#include "views/ViewManager.h"
#include "game/Game.h"
#include "controller/Controller.h"

#include <unordered_set>
#include <string>

std::unordered_set<std::string> parse_argv(int argc, char* argv[])
{
	std::unordered_set<std::string> arguments;
	for (int i = 1; i < argc; i++) {
		std::string arg = argv[i];
		arguments.emplace(arg);
	}
	return arguments;
}

std::map<std::string, std::unique_ptr<BlockFactory>> BlockFactory::_factories;
BlockFactoryInitializer BlockFactoryInitializer::si;

int main(int argc, char* argv[])
{
	auto arguments = parse_argv(argc, argv);

	Game game;
	Controller ctrl(game);
	ViewManager views;

	GraphicsView gv("Quadris", &game, &ctrl);
	ConsoleView cv(&game, &ctrl, std::cin, std::cout);

	views.push(&gv);
	views.push(&cv);

	while (game.isRunning()) {
		ctrl.send_commands();
		views.pollInput();
	}

	return 0;
}
