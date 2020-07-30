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
	void _clearConsole(void);
	void _prepareDisplay(std::string& display, const Board& board);
	void _addInfo(int row, std::string& display);

	// Trie methods
	void _buildTrie(void);
	std::vector<Command> _processCommand(const std::string&) const;

	std::shared_ptr<Trie> _trie;
	std::istream& _in;
	std::ostream& _out;
	std::thread _in_thread;
};

#endif // CONSOLEVIEW_H
