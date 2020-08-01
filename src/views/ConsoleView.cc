#include "ConsoleView.h"

#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <unordered_set>

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
	std::unordered_set<CommandType> invalidMultipliers = { 	CMD::RANDOM, 
															CMD::RESTART, 
															CMD::HINT, 
															CMD::NORANDOM_FILE, 
															CMD::SEQUENCE_FILE
														};
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
	matchingCommand.silent = true;

	if (invalidMultipliers.find(matchingCommand.type) != invalidMultipliers.end()) // force multipler of 1
		multiplier = 1;

	if (matchingCommand.type == CMD::QUIT)
		this->_issuedQuitCmd = true;

	if (matchingCommand.type != CMD::UNDEFINED_COMMAND) {
		for (int i = 0; i < multiplier; i++)
			commands.push_back(matchingCommand);
	}
	if (!commands.empty())
		commands.back().silent = false;
	return commands;
}

bool ConsoleView::_isValidFilePath(const std::string& filePath) {
	std::ifstream infile(filePath);
    return infile.good();
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
			std::vector<Command> payload = this->_processCommand(command);

			bool valid = !payload.empty();

			if (payload.size() == 1) {
				CommandType type = payload.at(0).type;
				// attach filePath to command
				if (type == CMD::NORANDOM_FILE || type == CMD::SEQUENCE_FILE) { 
					std::string filePath;
					this->_in >> filePath;
					if (this->_isValidFilePath(filePath)) {
						payload.at(0).message = filePath;
					} else {
						valid = false;
					}
				}
			}

			if (valid)
				this->_controller->push(payload);
			else
				this->update(); //requery

			// when quitting, kill thread immediately
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

void ConsoleView::_clearConsole(void)
{
	if (&this->_out != &std::cout || system(nullptr) == 0) {
		std::cerr << "ERROR: cannot clear this console\n";
	} else if (!(system("clear") == 0 || system("cls") == 0)) {
		std::cerr << "ERROR: failed to clear console\n";
	}
}

void ConsoleView::_displayGame(const Board& board)
{
	std::string display; // next console frame
	std::vector<char> boardChars = this->_createBoardChars(board);
	std::vector<std::string> next = this->_createNextStrings(board);
	this->_prepareDisplay(display, boardChars, next);
	// this->_clearConsole();
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

std::vector<std::string> ConsoleView::_createNextStrings(const Board& board)
{
	std::vector<std::string> next = { "        ", "        ", "        ", "        " };
	std::shared_ptr<Block> nextBlock = board.getNextBlock();
	if (nextBlock == nullptr)
		return next;
	nextBlock->blockSpace(true);
	for (auto& cell : nextBlock->getCells())
		next.at(cell->get_y()).at(2 * cell->get_x()) = cell->getToken();
	nextBlock->blockSpace(false);
	return next;
}

void ConsoleView::_prepareDisplay(std::string& display, std::vector<char>& boardChars, std::vector<std::string>& next)
{
	display.append(quadrisTitle);
	int row = 1;
	int rowCount = 0;
	std::string board_string = "   1      ";
	for (auto& c : boardChars) {
		if (rowCount == 11) {
			// add text to the right of the quadris board (if applicable)
			this->_addInfo(row, board_string, next);
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

void ConsoleView::_addInfo(int row, std::string& display, std::vector<std::string>& next)
{
	std::string info;
	int level;
	int score;
	int highScore;
	if ((2 <= row && row <= 4) || (8 <= row && row <= 12))
		info.append("    │ ");

	switch (row) {
	case 2:
		level = this->_game->getLevel();
		info.append("level: " + std::to_string(level));
		break;
	case 3:
		score = this->_game->getScore();
		info.append("score: " + std::to_string(score));
		break;
	case 4:
		highScore = this->_game->getHighScore();
		info.append("high score: " + std::to_string(highScore));
		break;
	case 1:
	case 7:
		info.append("    ┌────────────────────┐");
		break;
	case 5:
	case 13:
		info.append("    └────────────────────┘");
		break;
	case 8:
		info.append("next:");
		break;
	case 9:
		info.append(next.at(0));
		break;
	case 10:
		info.append(next.at(1));
		break;
	case 11:
		info.append(next.at(2));
		break;
	case 12:
		info.append(next.at(3));
		break;
	default:
		return;
	}
	// right hand side of info text box
	if ((2 <= row && row <= 4) || (8 <= row && row <= 12)) {
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
