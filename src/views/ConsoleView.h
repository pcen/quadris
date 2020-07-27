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

	void notify(void) const override;

private:
	// Display methods
	void _displayGame(void);
	void _clearConsole(void);
	void _writeTitle(void);
	void _drawBoard(void);
	void _addInfo(int row, std::string& line);

	// Trie methods
	void _buildTrie(void);
	std::vector<Command> _processCommand(const std::string&) const;

	std::shared_ptr<Trie> _trie;
	std::istream& _in;
	std::ostream& _out;
	std::thread _in_thread;

	Board _board;
};

#endif // CONSOLEVIEW_H
