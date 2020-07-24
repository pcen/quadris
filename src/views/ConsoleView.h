#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include "View.h"
#include "../generic/Trie.h"
#include "../game/Game.h"

#include <iostream>
#include <thread>

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
	void _clearConsole(void);
	void _writeTitle(void);

	std::istream& _in;
	std::ostream& _out;
	std::thread _in_thread;
};

#endif // CONSOLEVIEW_H
