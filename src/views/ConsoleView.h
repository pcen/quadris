#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include <future>
#include <thread>
#include <iostream>

#include "View.h"
#include "../generic/Trie.h"
#include "../game/Game.h"

class ConsoleView : public View
{
public:

	ConsoleView(std::istream& in, Game* game);

	std::future<void> start();

private:
	std::istream& _in;
	Game* _game;
};

#endif // CONSOLEVIEW_H
