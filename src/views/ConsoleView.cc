#include "ConsoleView.h"

void poll_console_input(std::istream& in, Game* game)
{
	std::string command;
	while (game->is_running()) {
		in >> command;

		// TODO: route this through controller class

		// Since the game may terminate while waiting for
		// input, check if the game is still running before
		// sending the command
		if (game != nullptr && game->is_running())
			game->update(command);
	}
}

ConsoleView::ConsoleView(std::istream& in, Game* game)
	: View{ game }, _in{ in }
{

}

std::future<void> ConsoleView::start(void)
{
	return std::async(std::launch::async, [&](){
		return poll_console_input(_in, _game);
	});
}

void ConsoleView::update(void) const
{
	std::cerr << "ConsoleView::update\n";
	if (!_game->is_running()) {
		// TODO: somehow kill waiting for in >> command
	}
}
