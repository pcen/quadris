#include "Game.h"

#include <iostream>
#include <string>

#include "./blocks/StandardBlocks.h"
Game::Game(std::string filePath)
	: _board("./assets/_.png"), _running{true}, _score{0}, _highScore{0}
{
	std::shared_ptr<std::ifstream> sequenceFile = std::make_shared<std::ifstream>();
	this->_level = std::make_unique<Level0>(filePath, this, true, sequenceFile);
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
		auto nextBlock = this->_level->getNextBlock();
		if (this->_board.setCurrentBlock(nextBlock) == false) {
			// if a new block cannot be added, the game is over
			this->_updateScore();
			this->restart();
			std::cerr << "Game Over!\n";
		}
	}

	if (!command.silent)
		this->_notify();
}

void Game::launch(void)
{
	auto firstBlock = this->_level->getNextBlock();
	if (this->_board.setCurrentBlock(firstBlock) == false) {
		std::cerr << "could not add first block\n";
	}
	this->_notify();
}

void Game::restart(void)
{
	this->_board.reset();
	auto nextBlock = this->_level->getNextBlock();
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
