#include "Game.h"

#include <iostream>
#include <string>

#include "./blocks/StandardBlocks.h"

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
	bool collided = false;

	switch(command.type) {
	case CMD::QUIT:
		this->_running = false;
		break;

	case CMD::DOWN:
		collided = this->_board.moveY(false);
		break;

	default:
		break;
	}

	if (collided) {
		auto nextBlock = std::make_shared<IBlock>(this->_level->getLevel()); // this->_level->getNextBlock();
		this->_board.setCurrentBlock(nextBlock);
		// put next block on the board
	}

	this->_notify();
}

void Game::launch(void)
{
	auto firstBlock = std::make_shared<IBlock>(this->_level->getLevel());
	this->_board.setCurrentBlock(firstBlock);
	this->_notify();
}

void Game::restart(void)
{

}

bool Game::isRunning(void) const
{
	return this->_running;
}
