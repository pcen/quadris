#include "Game.h"

#include <iostream>
#include <string>

Game::Game()
	: _board("./assets/_.png"), _running{true}, _score{0}, _highScore{0}
{
	_level = std::make_unique<Level0>(std::string("././src/game/sequence.txt"), this, true);
}

Game::~Game()
{

}

const Board& Game::getBoard(void) const
{
	return this->_board;
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
