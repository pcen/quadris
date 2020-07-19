#include "ConsoleView.h"

ConsoleView::ConsoleView(Game* game, CommandInterpreter* interpreter, std::istream& in)
	: View{ game, interpreter }, _in{ in }
{
	// spin thread to read _in stream
	this->_in_thread = std::thread(&ConsoleView::read_in_stream, this);
}

ConsoleView::~ConsoleView()
{
	// join the _in_thread before application exits
	if (this->_in_thread.joinable())
		this->_in_thread.join();
}

void ConsoleView::read_in_stream(void)
{
	std::cerr << "in stream thread start\n";
	std::string command;
	while (_game->is_running()) {
		_in >> command;

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
	std::cerr << "in stream thread end\n";
}

void ConsoleView::poll_input(void)
{
	// input stream must be polled from separate thread
}

void ConsoleView::notify(void) const
{
	std::cerr << "ConsoleView::notify\n";
	if (!_game->is_running()) {
		std::cerr << "ConsoleView updated from game that's not running\n";
		// TODO: somehow kill waiting for in >> command
	}
}
