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
	: View{ game, controller }, _issuedQuitCmd{ false }, _in{ in }, _out{ out }
{
	// spin thread to read _in stream
	this->_in_thread = std::thread(&ConsoleView::readInStream, this);

	// construct trie
	this->_trie = std::make_shared<Trie>();
	this->_buildTrie();

	this->_clearConsole();
}

ConsoleView::~ConsoleView()
{
	// clean up console otherwise input box artifacts remain
	// this->_clearConsole();

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
		_trie->push(command, (CommandType) id);
}

std::vector<Command> ConsoleView::_processCommand(const std::string& s)
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

	if (matchingCommand.type == CMD::QUIT)
		this->_issuedQuitCmd = true;

	if (matchingCommand.type != CMD::UNDEFINED_COMMAND) {
		for (int i = 0; i < multiplier; i++)
			commands.push_back(matchingCommand);
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
		// TODO: EOF should terminate
		this->_in >> command;

		// Since the game may terminate while waiting for input, check if the
		// game is still running before  sending the command
		if (this->_game != nullptr && this->_game->isRunning()) {
			this->_controller->push(this->_processCommand(command));

			// when quitting, kill thread immediately
			Command c = _trie->findShortestPrefix(command);
			if (this->_issuedQuitCmd) {
				if (this->_game != nullptr) {
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
		}
	}
}

void ConsoleView::_displayGame(const Board& board)
{
	std::string display; // next console frame
	std::vector<char> boardChars = this->_createBoardChars(board);
	this->_prepareDisplay(display, boardChars);
	this->_clearConsole();
	this->_out << display;
	this->_out.flush();
}

std::vector<char> ConsoleView::_createBoardChars(const Board& board)
{
	// prepare board as a vector of their char representations
	std::vector<char> boardChars;
	for (auto i = board.begin(); i != board.end(); ++i) {
		boardChars.push_back((*i).getToken());
	}
	// overlay the active block's cells, if any
	auto currentBlock = board.getCurrentBlock();
	if (currentBlock != nullptr) {
		auto cells = currentBlock->getCells();
		for (auto& c : cells) {
			int x = c->get_x();
			// top of board is flipped in display
			int y = 17 - c->get_y();
			unsigned int index = 11 * y + x;
			if (index < boardChars.size())
				boardChars.at(index) = c->getToken();
			else
				std::cerr << "ERROR: currentBlock outside of board\n";
		}
	}
	return boardChars;
}

void ConsoleView::_clearConsole(void)
{
	if (&this->_out != &std::cout || system(nullptr) == 0) {
		std::cerr << "ERROR: cannot clear this console\n";
	} else if (!(system("clear") == 0 || system("cls") == 0)) {
		std::cerr << "ERROR: failed to clear console\n";
	}
}

void ConsoleView::_prepareDisplay(std::string& display, std::vector<char>& boardChars)
{
	display.append(quadrisTitle);
	int row = 1;
	int rowCount = 0;
	std::string board_string = "   1      ";
	for (auto& c : boardChars) {
		if (rowCount == 11) {
			// add text to the right of the quadris board (if applicable)
			this->_addInfo(row, board_string);
			row++;
			board_string.append("\n   " + std::to_string(row)); // add row number
			board_string.append(std::string(6 - (row / 10), ' ')); // pad to board
			rowCount = 1;
		} else {
			rowCount++;
		}

		board_string.append(std::string(1, c)); // add cell token
		board_string.append(" "); // add space between cells
	}
	display.append(board_string);
	display.append("\n┌────────────────────────────────────────────────────────┐\n");
	display.append("│ >                                                      │\n");
	display.append("└────────────────────────────────────────────────────────┘");
	display.append("\x1b[A");
	display.append("\r│ > ");
}

void ConsoleView::_addInfo(int row, std::string& display)
{
	std::string info;
	if (2 <= row && row <= 4)
		info.append("    │ ");

	switch (row) {
	case 2:
		info.append("level: 69");
		break;
	case 3:
		info.append("score: 420");
		break;
	case 4:
		info.append("high score: 42069");
		break;
	case 1:
		info.append("    ┌────────────────────┐");
		break;
	case 5:
		info.append("    └────────────────────┘");
		break;
	default:
		return;
	}
	// right hand side of info text box
	if (2 <= row && row <= 4) {
		info.append(std::string(27 - info.length(), ' '));
		info.append("│");
	}
	display.append(info);
}

void ConsoleView::pollInput(void)
{
	// input stream must be polled from separate thread and not here
}

void ConsoleView::update(void)
{
	const Board& board = this->_game->getBoard();
	this->_displayGame(board);
}

// A normal ConsoleView tied to the program's execution and thus is
// open as long as the instance exists
bool ConsoleView::isOpen(void) const
{
	return true;
}
