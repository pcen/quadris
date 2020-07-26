#include "Game.h"

#include <iostream>

using namespace std;

Game::Game()
	: _running{true}, _level{make_unique<Level0>()}, _difficulty{0},
	_score{0}, _highScore{0}, _random{false}
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
