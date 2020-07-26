#include "ConsoleView.h"

#include <stdlib.h>
#include <fstream>

// generated with: http://patorjk.com/software/taag/#p=display&f=Small&t=Quadris
static const char* quadrisTitle =
"   ___               _     _    \n"
"  / _ \\ _  _ __ _ __| |_ _(_)___\n"
" | (_) | || / _` / _` | '_| (_-<\n"
"  \\__\\_\\\\_,_\\__,_\\__,_|_| |_/__/\n";

ConsoleView::ConsoleView(Game* game, Controller* controller, std::istream& in, std::ostream& out)
	: View{ game, controller }, _in{ in }, _out{ out }
{
	// spin thread to read _in stream
	this->_in_thread = std::thread(&ConsoleView::readInStream, this);
	this->_trie = std::make_shared<Trie>();
	this->_buildTrie();
}

ConsoleView::~ConsoleView()
{
	// join the _in_thread before application exits
	if (this->_in_thread.joinable())
		this->_in_thread.join();
}

void ConsoleView::_buildTrie()
{
	std::ifstream infile("./src/controller/commands.txt");

	std::string command;
	int id;
	while (infile >> command >> id)
	{
		_trie->push(command, (CommandType) id);
	}
}

std::vector<Command> ConsoleView::_processCommand(const std::string& s) const
{
	std::vector<Command> commands;

	unsigned int split = 0;

	for (; split < s.length(); split++) {
		char c = s[split];
		if (c > '9' || c < '0')
			break;
	}

	std::string multiplierString = s.substr(0, split);
	int multiplier = multiplierString.length() ? std::stoi(multiplierString) : 1;
  	std::string command = s.substr(split);

	Command matchingCommand = _trie->findShortestPrefix(command);

	if (matchingCommand.type != CommandType::UNDEFINED_COMMAND) {
		for (int i = 0; i < multiplier; i++) {
			commands.push_back(matchingCommand);
		}
	}

	return commands;
}

// read_in_stream runs in separate thread for the lifetime
// of a ConsoleView instance. This method may attempt to
// call methods of Controller, and Subject::unsubscribe,
// so these classes / methods should ensure that data members are
// thread safe in instances where read_in_stream may call them
void ConsoleView::readInStream(void)
{
	std::string command;
	while (this->_game->isRunning()) {
		_in >> command;

		// Since the game may terminate while waiting for input, check if the
		// game is still running before  sending the command
		if (this->_game != nullptr && this->_game->isRunning()) {
			this->_controller->push(this->_processCommand(command));

			// when quitting, kill thread immediately
			if (command == "quit") {
				if (this->_game != nullptr) // TODO make shutdown a View method?
					this->_game->unsubscribe(this);
				this->_subscribed = false;
				return;
			}
			if (command == "clear") {
				this->_clearConsole();
			}
			if (command == "title") {
				this->_writeTitle();
			}

		}
	}
}

void ConsoleView::_clearConsole(void)
{
	if (&this->_out != &std::cout) {
		std::cerr << "ERROR: clearing this console is not supported\n";
		return;
	}
	if (system(nullptr) == 0) {
		std::cerr << "ERROR: system not available\n";
		return;
	}
	if (system("clear") == 0) {
		return;
	}
	if (system("cls") == 0) {
		return;
	}
	std::cerr << "ERROR: failed to clear console\n";
}

void ConsoleView::_writeTitle(void)
{
	this->_out << quadrisTitle;
}

void ConsoleView::pollInput(void)
{
	// input stream must be polled from separate thread
	// TODO: maybe here if game is not running the input stream thread
	//       can somehow be killed so the user in not requred to type "quit"
}

void ConsoleView::notify(void) const
{
	if (!this->_game->isRunning()) {
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
