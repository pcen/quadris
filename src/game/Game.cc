#include "Game.h"

#include <iostream>
#include <string>

Game::Game()
	: _running{true}, _difficulty{0}, _board("./assets/_.png"), _score{0}, _highScore{0}, _random{false}
{
	_level = std::make_unique<Level0>(std::string("././src/game/sequence.txt"), this, true);
}

Game::~Game()
{
	_level->_game = nullptr;
}

const Board& Game::getBoard(void) const
{
	return this->_board;
}

const std::vector<Coord> Game::getBoardChanges(void)
{
	return this->_board._boardChanges;
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

	// all observers have had the chance to see board changes
	this->_board._boardChanges.clear();
}

bool Game::isRunning(void) const
{
	return this->_running;
}
