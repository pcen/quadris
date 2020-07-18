#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include <iostream>

#include "View.h"
#include "../generic/Trie.h"
#include "../game/Game.h"

class ConsoleView : public View
{
public:
	ConsoleView(std::istream& in, Game* game);
	std::future<void> start(void) override;
	void update(void) const override;

private:
	std::istream& _in;
};

#endif // CONSOLEVIEW_H
