#include "View.h"

#include <iostream>
#include <sstream>
#include <thread>

View::View(Game* game, CommandInterpreter* interpreter)
	: _game{ game }, _interpreter{ interpreter }
{
	_game->subscribe(this);
}

View::~View()
{
	if (_game != nullptr)
		_game->unsubscribe(this);
}

void View::notify(void) const
{
	std::cerr << "!!! View::notify\n";
}

std::string View::get_thread_id(void) const
{
	std::stringstream ss;
	ss << std::this_thread::get_id();
	std::string thread_id = ss.str();
	return thread_id;
}
