#include "ConsoleView.h"

void poll_console_input(std::istream& in, Game* game)
{
	std::string command;
	while (game->is_running()) {
		in >> command;
		game->update(command);
	}
}

ConsoleView::ConsoleView(std::istream& in, Game* game)
	: _in{ in }, _game{ game }
{

}

std::future<void> ConsoleView::start(void)
{
	return std::async(std::launch::async, [&](){
		return poll_console_input(_in, _game);
	});
}
