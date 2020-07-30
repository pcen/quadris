#include <iostream>

#include "views/ConsoleView.h"
#include "views/GraphicsView.h"
#include "views/ViewManager.h"
#include "game/Game.h"
#include "controller/Controller.h"

#include <unordered_set>
#include <string>

class Arguments
{
public:
	Arguments(int argc, char* argv[])
	{
		for (int i = 1; i < argc; i++) {
			std::string arg = argv[i];
			_arguments.emplace(arg);
		}
	}
	bool has(const std::string& arg)
	{
		return this->_arguments.find(arg) != this->_arguments.end();
	}

private:
	std::unordered_set<std::string> _arguments;
};

int main(int argc, char* argv[])
{
	auto args = Arguments(argc, argv);

	Game game;
	Controller ctrl(game);
	ViewManager views;

	auto cv = std::make_shared<ConsoleView>(&game, &ctrl, std::cin, std::cout);
	views.push(cv);

	if (!args.has("-text")) {
		auto gv = std::make_shared<GraphicsView>("Quadris", &game, &ctrl);
		views.push(gv);
	}

	while (game.isRunning()) {
		ctrl.send_commands();
		views.pollInput();
	}

	return 0;
}
