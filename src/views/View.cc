#include "View.h"

#include <iostream>
#include <sstream>
#include <thread>

View::View(Game* game, Controller* controller)
	: _game{ game }, _controller{ controller }
{
	this->_game->subscribe(this);
	this->_subscribed = true;
}

View::~View()
{
	if (this->_game != nullptr && _subscribed)
		this->_game->unsubscribe(this);
}
