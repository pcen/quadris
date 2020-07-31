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
	bool dropped = false;

	switch(command.type) {
		case CMD::QUIT:
			this->_running = false;
			break;
		case CMD::DOWN:
			this->_board.translate(Direction::DOWN);
			break;
		case CMD::LEFT:
			this->_board.translate(Direction::LEFT);
			break;
		case CMD::RIGHT:
			this->_board.translate(Direction::RIGHT);
			break;
		case CMD::DROP:
			this->_board.drop();
			dropped = true;
			break;
		case CMD::RESTART:
			this->restart();
			break;
		default:
			break;
	}

	if (dropped) {
		// put next block on the board
		this->_board.insertCurrentBlock();
		auto nextBlock = std::make_shared<IBlock>(this->_level->getLevel()); // this->_level->getNextBlock();
		if (this->_board.setCurrentBlock(nextBlock) == false) {
			// if a new block cannot be added, the game is over
			this->_updateScore();
			this->restart();
			std::cerr << "Game Over!\n";
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
	this->_board.reset();
	auto nextBlock = std::make_shared<IBlock>(this->_level->getLevel()); // this->_level->getNextBlock();
	if (this->_board.setCurrentBlock(nextBlock) == false) {
		std::cerr << "could not add next block\n";
	}
}

bool Game::isRunning(void) const
{
	return this->_running;
}

void Game::_updateScore(void)
{
	// TODO: implement
}
