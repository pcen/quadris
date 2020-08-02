#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

#include "views/ConsoleView.h"
#include "views/GraphicsView.h"
#include "views/ViewManager.h"
#include "game/Game.h"
#include "controller/Controller.h"

class Arguments
{
public:
	Arguments(int argc, char* argv[])
	{
		for (int i = 1; i < argc; i++) {
			std::string arg = argv[i];
			_arguments.emplace_back(arg);
		}
	}
	std::vector<std::string>::iterator find(const std::string& loc)
	{
		return std::find(this->_arguments.begin(), this->_arguments.end(), loc);
	}
	bool has(const std::string& arg)
	{
		return this->find(arg) != this->_arguments.end();
	}
	std::string getParam(const std::string& param)
	{
		return *(++this->find(param));
	}

private:
	std::vector<std::string> _arguments;
};

int main(int argc, char* argv[])
{
	auto args = Arguments(argc, argv);

	// set start level
	unsigned int startLevel = 0;
	if (args.has("-startlevel"))
		startLevel = std::stoi(args.getParam("-startlevel"));

	// seed PRNG std::rand
	if (args.has("-seed")) {
		unsigned int seed = std::stoi(args.getParam("-seed"));
		std::srand(seed);
	}

	// TODO: set script file
	std::string script;
	bool useScript = false;
	if (args.has("-scriptfile")) {
		script = args.getParam("-scriptfile");
		// TODO: check if script file exists
		useScript = true;
	}

	Game game(startLevel, std::string("./src/game/sequence.txt"));
	Controller ctrl(game);
	ViewManager views;

	// add graphics view
	if (!args.has("-text")) {
		auto gv = std::make_shared<GraphicsView>("Quadris", &game, &ctrl);
		views.push(gv);
	}

	script = "./tests/score.in";
	std::ifstream ifs;
	ifs.open(script);

	// add console view
	auto cv = std::make_shared<ConsoleView>(&game, &ctrl, ifs, std::cout);
	views.push(cv);

	game.launch();
	while (game.isRunning()) {
		ctrl.sendCommands();
		views.pollInput();
	}

	ifs.close();

	return 0;
}
