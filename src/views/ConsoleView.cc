#include "ConsoleView.h"

ConsoleView::ConsoleView(std::istream& in, Game* game)
	: View{ game }, _in{ in }
{

}

void ConsoleView::start(void)
{
	std::string command;
	while (_game->is_running()) {
		_in >> command;

		// TODO: route this through controller class

		// Since the game may terminate while waiting for
		// input, check if the game is still running before
		// sending the command
		if (_game != nullptr && _game->is_running())
			_game->update(command);
	}
}

void ConsoleView::update(void) const
{
	std::cerr << "ConsoleView::update\n";
	if (!_game->is_running()) {
		// TODO: somehow kill waiting for in >> command
	}
}

std::future<void> ConsoleView::create(Game* game)
{
	return std::async(std::launch::async, [game](){
		std::cerr << "creating console view\n";
		ConsoleView cv(std::cin, game);
		cv.start();
		std::cerr << "console view thread closed\n";
	});
}
