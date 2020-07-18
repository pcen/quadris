#include "Game.h"

#include <iostream>

Game::Game()
	: _running{ true }
{

}

void Game::update(const std::string& command)
{
	std::cerr << "Game::update: " << command << "\n";

	if (command == "quit")
		this->_running = false;
}

bool Game::is_running(void) const
{
	return this->_running;
}
