#include "View.h"

#include <iostream>

View::View(Game* game)
	: _game{ game }
{
	_game->subscribe(this);
}

View::~View()
{
	if (_game != nullptr)
		_game->unsubscribe(this);
}

void View::update(void) const
{
	std::cerr << "View::update\n";
}
