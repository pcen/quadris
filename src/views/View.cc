#include "View.h"

#include <iostream>
#include <sstream>
#include <thread>

View::View(Game* game, CommandInterpreter* interpreter)
	: _game{ game }, _interpreter{ interpreter }
{
	_game->subscribe(this);
	_subscribed = true;
}

View::~View()
{
	if (_game != nullptr && _subscribed)
		_game->unsubscribe(this);
}
