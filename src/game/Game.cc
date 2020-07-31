#include "Game.h"

#include <iostream>
#include <string>

Game::Game(std::string filePath)
	: _board("./assets/_.png"), _running{true}, _score{0}, _highScore{0}
{
	std::shared_ptr<std::ifstream> sequenceFile = std::make_shared<std::ifstream>();
	_level = std::make_unique<Level0>(filePath, this, true, sequenceFile);
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
