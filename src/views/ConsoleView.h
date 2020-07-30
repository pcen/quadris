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
	void _displayGame(const Board& board) const;
	void _clearConsole(void) const;
	void _writeTitle(void) const;
	void _drawBoard(const Board& board) const;
	void _addInfo(int row, std::string& line) const;
	void _drawInputPrompt(void) const;

	// Trie methods
	void _buildTrie(void);
	std::vector<Command> _processCommand(const std::string&) const;

	std::shared_ptr<Trie> _trie;
	std::istream& _in;
	std::ostream& _out;
	std::thread _in_thread;
};

#endif // CONSOLEVIEW_H
