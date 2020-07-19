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

// read_in_stream runs in separate thread for the lifetime
// of a ConsoleView instance. This method may attempt to
// call methods of CommandInterpreter, and Subject::unsubscribe,
// so these classes / methods should ensure that data members are
// thread safe in instances where read_in_stream may call them
void ConsoleView::read_in_stream(void)
{
	std::cerr << "read_in_stream thread start\n";
	std::string command;
	while (_game->is_running()) {
		_in >> command;

		// Since the game may terminate while waiting for input, check if the
		// game is still running before  sending the command
		if (_game != nullptr && _game->is_running()) {
			_interpreter->push(command);

			// when quitting, kill thread immediately
			if (command == "quit") {
				if (this->_game != nullptr) // TODO make shutdown a View method?
					_game->unsubscribe(this);
				_subscribed = false;
				return;
			}
		}
	}
	std::cerr << "read_in_stream thread end\n";
}

void ConsoleView::poll_input(void)
{
	// input stream must be polled from separate thread
	// TODO: maybe here if game is not running the input stream thread
	//       can somehow be killed so the user in not requred to type "quit"
}

void ConsoleView::notify(void) const
{
	std::cerr << "ConsoleView::notify\n";
	if (!_game->is_running()) {
		std::cerr << "ConsoleView updated from game that's not running\n";
		// TODO: somehow kill waiting for in >> command
	}
}

// A normal ConsoleView tied to the program's execution and thus is
// open as long as the instance exists
bool ConsoleView::isOpen(void) const
{
	return true;
}
