#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include <iostream>
#include <thread>

#include "View.h"
#include "../game/Game.h"
#include "../generic/Trie.h"

class ConsoleView : public View
{
public:
	ConsoleView(Game* game, Controller* controller, std::istream& in, std::ostream& out);
	~ConsoleView();

	void pollInput(void) override;
	void readInStream(void);
	bool isOpen(void) const override;

	void update(void) override;

private:
	// Display methods
	void _displayGame(const Board& board);
	std::vector<char> _createBoardChars(const Board& board);
	std::vector<std::string> _createNextStrings(const Board& board);
	void _clearConsole(void);
	void _prepareDisplay(std::string& display, std::vector<char>& boardChars, std::vector<std::string>& next);
	void _addInfo(int row, std::string& display, std::vector<std::string>& next);

	// Trie methods
	void _buildTrie(void);
	std::vector<Command> _processCommand(const std::string&);

	bool _isValidFilePath(const std::string& filePath);
	
	bool _issuedQuitCmd;
	std::shared_ptr<Trie> _trie;
	std::istream& _in;
	std::ostream& _out;
	std::thread _in_thread;
};

#endif // CONSOLEVIEW_H
