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
	ConsoleView(Game* game, CommandInterpreter* interpreter, std::istream& in);
	~ConsoleView();

	void poll_input(void) override;
	void read_in_stream(void);
	bool isOpen(void) const override;

	void notify(void) const override;

public:
	std::istream& _in;
	std::thread _in_thread;
};

#endif // CONSOLEVIEW_H
