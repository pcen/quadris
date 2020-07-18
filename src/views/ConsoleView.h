#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include "View.h"
#include "../generic/Trie.h"
#include "../game/Game.h"

#include <iostream>
#include <future>

class ConsoleView : public View
{
public:
	ConsoleView(Game* game);
	void start(void) override;
	void notify(void) const override;

	static std::future<void> create(Game* game);
};

#endif // CONSOLEVIEW_H
