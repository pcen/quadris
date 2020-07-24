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
	ConsoleView(Game* game, Controller* controller, std::istream& in);
	~ConsoleView();

	void pollInput(void) override;
	void readInStream(void);
	bool isOpen(void) const override;

	void notify(void) const override;

private:
	void _clearConsole(void);

	std::istream& _in;
	std::thread _in_thread;
};

#endif // CONSOLEVIEW_H
