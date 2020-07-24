#include "Game.h"

#include <iostream>

Game::Game()
	: _running{ true }
{

}

Game::~Game()
{

}

void Game::update(const Command& command)
{
	switch(command.type) {
	case CMD::QUIT:
		this->_running = false;
		break;
	default:
		break;
	}

	this->_notify();
}

bool Game::isRunning(void) const
{
	return this->_running;
}
