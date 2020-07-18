#include "ConsoleView.h"

ConsoleView::ConsoleView(Game* game, CommandInterpreter* interpreter)
	: View{ game, interpreter }
{

}

void ConsoleView::start(void)
{
	std::string command;
	while (_game->is_running()) {
		std::cin >> command;

		// Since the game may terminate while waiting for
		// input, check if the game is still running before
		// sending the command
		if (_game != nullptr && _game->is_running()) {
			_interpreter->push(command);
			// when quitting, kill thread immediately
			if (command == "quit")
				return;
		}
	}
}

void ConsoleView::notify(void) const
{
	std::cerr << "ConsoleView::notify\n";
	std::cerr << "Thread ID " << get_thread_id() << "\n";
	if (!_game->is_running()) {
		// TODO: somehow kill waiting for in >> command
	}
}

std::future<void> ConsoleView::create(Game* game, CommandInterpreter* interpreter)
{
	return std::async(std::launch::async, [game, interpreter](){
		ConsoleView cv(game, interpreter);
		std::cerr << "console view thread: " << cv.get_thread_id() << "\n";
		cv.start();
		std::cerr << "console view thread closed\n";
	});
}
