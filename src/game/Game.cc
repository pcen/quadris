#include "Game.h"

#include <iostream>
#include <string>

#include "./blocks/StandardBlocks.h"

Game::Game()
	: _board("./assets/_.png"), _running{true}, _score{0}, _highScore{0}
{
	_level = std::make_unique<Level0>(std::string("./src/game/sequence.txt"), this, true);
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
	bool landed = false;
	bool translated = false;

	switch(command.type) {
		case CMD::QUIT:
			this->_running = false;
			break;
		case CMD::DOWN:
			translated = this->_board.translate(Direction::DOWN);
			break;
		case CMD::LEFT:
			translated = this->_board.translate(Direction::LEFT);
			break;
		case CMD::RIGHT:
			translated = this->_board.translate(Direction::RIGHT);
			break;
		case CMD::DROP:
			translated = this->_board.drop();
			// TODO: implement landing logic
			landed = true;
			break;
		default:
			break;
	}

	if (landed) {
		// put next block on the board
		this->_board.insertCurrentBlock();
		auto nextBlock = std::make_shared<IBlock>(this->_level->getLevel()); // this->_level->getNextBlock();
		if (this->_board.setCurrentBlock(nextBlock) == false) {
			std::cerr << "could not add next block\n";
		}
	}

	this->_notify();
}

void Game::launch(void)
{
	auto firstBlock = std::make_shared<IBlock>(this->_level->getLevel());
	if (this->_board.setCurrentBlock(firstBlock) == false) {
		std::cerr << "could not add first block\n";
	}
	this->_notify();
}

void Game::restart(void)
{

}

bool Game::isRunning(void) const
{
	return this->_running;
}
