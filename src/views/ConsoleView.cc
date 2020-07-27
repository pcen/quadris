#include "ConsoleView.h"

#include <stdlib.h>
#include <fstream>
#include <sstream>

// generated with: http://patorjk.com/software/taag/#p=display&f=Small&t=Quadris
// modifications to source material:
//    - added escaped characters to escape '\'
//    - added '\n' characters
static const char* quadrisTitle =
"   ___               _     _    \n"
"  / _ \\ _  _ __ _ __| |_ _(_)___\n"
" | (_) | || / _` / _` | '_| (_-<\n"
"  \\__\\_\\\\_,_\\__,_\\__,_|_| |_/__/\n\n";

ConsoleView::ConsoleView(Game* game, Controller* controller, std::istream& in, std::ostream& out)
	: View{ game, controller }, _in{ in }, _out{ out }
{
	// spin thread to read _in stream
	this->_in_thread = std::thread(&ConsoleView::readInStream, this);

	// construct trie
	this->_trie = std::make_shared<Trie>();
	this->_buildTrie();

	_board = Board("./assets/a.png");
	_clearConsole();
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
				if (this->_game != nullptr) {
					// TODO make shutdown a View method?

					// Here, this view closes itself in a separate thread, and
					// its base class may still exist when game begins notifying
					// observers it has recieved a "quit" command. To ensure
					// that game does not try to call notify on the virtual View
					// base class from which ConsoleView is described, unsubscribe
					// here. Unsubscribing ensures one of the following outcomes:
					// 1 - If game begins notifying observers before this line of
					//     code is reached, game's mutex will be locked (since
					//     Subject::_notify is a threadsafe method), so this line
					//     hangs until game calls notify on this class. This hang
					//     ensures that the ConsoleView instance still exists when
					//     game calls notify on this object
					// 2 - If this line executes before game begins notifying
					//     observers, game will hang upon calling _notify until
					//     this ConsoleView has finished unsubscribing, since
					//     unsubscribe is also a threadsafe method and will lock
					//     game's mutex, ensuring that game will not attempt to
					//     notify this console view while this has begun destructing
					this->_game->unsubscribe(this);
					this->_subscribed = false;
				}
				return;
			}
			if (command == "clear") {
				this->_clearConsole();
			}
			if (command == "title") {
				this->_writeTitle();
			}
			if (command == "render") {
				this->_displayGame();
			}
		}
	}
}

void ConsoleView::_displayGame(void)
{
	this->_clearConsole();
	this->_writeTitle();
	this->_drawBoard();
	this->_drawInputPrompt();
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
	if (system("clear") == 0 || system("cls") == 0) {
		return;
	}
	std::cerr << "ERROR: failed to clear console\n";
}

void ConsoleView::_writeTitle(void)
{
	this->_out << quadrisTitle;
}

void ConsoleView::_drawBoard(void)
{
	int row = 1;
	std::string row_string = "   1      ";
	for (auto i = this->_board.begin(); i != this->_board.end(); ++i) {
		std::shared_ptr<Cell> c = *i;

		if (c->get_y() + 1 > row) {
			row = c->get_y() + 1;

			// add text to the right of the quadris board (if applicable)
			this->_addInfo(row - 1, row_string);
			this->_out << row_string << "\n";

			row_string.clear();
			row_string.append("   " + std::to_string(row)); // add row number
			row_string.append(std::string(6 - row / 10, ' ')); // pad to board
		}

		row_string.append(std::string(1, c->getToken())); // add cell's token
		row_string.append(" "); // add space between cells
	}
	this->_out << row_string << "\n";
}

void ConsoleView::_addInfo(int row, std::string& line)
{
	// left hand side of info text box
	if (2 <= row && row <= 4)
		line.append("    │ ");

	switch (row) {
	case 2:
		line.append("level: 69");
		break;
	case 3:
		line.append("score: 420");
		break;
	case 4:
		line.append("high score: 42069");
		break;
	case 1:
		line.append("    ┌");
		line.append("────────────────────");
		line.append("┐");
		break;
	case 5:
		line.append("    └");
		line.append("────────────────────");
		line.append("┘");
		break;
	default:
		return;
	}
	// right hand side of info text box
	if (2 <= row && row <= 4) {
		line.append(std::string(59 - line.length(), ' '));
		line.append("│");
	}
}

void ConsoleView::_drawInputPrompt(void)
{
	this->_out << "┌────────────────────────────────────────────────────────┐\n";
	this->_out << "│ >                                                      │\n";
	this->_out << "└────────────────────────────────────────────────────────┘";
	this->_out << "\x1b[A" << "\r│ > ";
}

void ConsoleView::pollInput(void)
{
	// input stream must be polled from separate thread
	// TODO: maybe here if game is not running the input stream thread
	//       can somehow be killed so the user in not requred to type "quit"
}

void ConsoleView::notify(void) const
{

}

// A normal ConsoleView tied to the program's execution and thus is
// open as long as the instance exists
bool ConsoleView::isOpen(void) const
{
	return true;
}
