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

		// Since the game may terminate while waiting for input, check if the
		// game is still running before  sending the command
		if (_game != nullptr && _game->is_running()) {
			_interpreter->push(command);

			// when quitting, kill thread immediately
			if (command == "quit") {
				_game->unsubscribe(this);
				_subscribed = false;
				return;
			}
		}
	}
}

void ConsoleView::notify(void) const
{
	std::cerr << "ConsoleView notified on " << get_thread_id() << "\n";
	if (!_game->is_running()) {
		std::cerr << "ConsoleView updated from game that's not running\n";
		// TODO: somehow kill waiting for in >> command
	}
}

std::future<void> ConsoleView::create(Game* game, CommandInterpreter* interpreter)
{
	return std::async(std::launch::async, [game, interpreter](){
		ConsoleView cv(game, interpreter);
		std::cerr << "console view thread: " << cv.get_thread_id() << "\n";
		cv.start();
		std::cerr << "console view thread returning\n";
	});
}
