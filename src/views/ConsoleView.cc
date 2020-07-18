#include "ConsoleView.h"

ConsoleView::ConsoleView(Game* game)
	: View{ game }
{

}

void ConsoleView::start(void)
{
	std::string command;
	while (_game->is_running()) {
		std::cin >> command;

		// TODO: route this through controller class

		// Since the game may terminate while waiting for
		// input, check if the game is still running before
		// sending the command
		if (_game != nullptr && _game->is_running())
			_game->update(command);
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

std::future<void> ConsoleView::create(Game* game)
{
	return std::async(std::launch::async, [game](){
		ConsoleView cv(game);
		std::cerr << "console view thread: " << cv.get_thread_id() << "\n";
		cv.start();
		std::cerr << "console view thread closed\n";
	});
}
