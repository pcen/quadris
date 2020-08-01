#include "Game.h"

#include <iostream>
#include <string>

#include "./blocks/StandardBlocks.h"
Game::Game(uint startLevel, std::string filePath)
	: _board("./assets/_.png"), _defaultSequence{ filePath }, _running{true},
	_score{0}, _highScore{0}, _startLevel{startLevel}
{
	std::shared_ptr<std::ifstream> sequenceFile = std::make_shared<std::ifstream>();
	this->_level = LevelFactory::createLevel(startLevel, filePath, this, true, sequenceFile);
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
	bool rotated = false;

	switch(command.type) {
		case CMD::QUIT:
			this->_running = false;
			break;

		case CMD::CLOCKWISE:
		case CMD::COUNTERCLOCKWISE:
			rotated = this->_board.rotate(command.type == CMD::CLOCKWISE);
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
			break;

		case CMD::RESTART:
			this->restart();
			break;

		case CMD::LEVELUP:
			this->levelup();
			break;

		case CMD::LEVELDOWN:
			this->leveldown();
			break;

		// random block generation (sequence file remains unchanged)
		case CMD::RANDOM:
			this->_level->useRandom(true);
			break;

		// non-random block generation from the specified sequence file
		case CMD::NORANDOM_FILE:
			// ignore when level number is less than 3
			if (this->_level->getLevel() < 3)
				return;
			this->_level->openSequence(command.message);
			this->_level->useRandom(false);
			break;

		// run a sequence of commands from a file (for testing)
		case CMD::SEQUENCE_FILE:
			// set a new sequence file
			break;

		default:
			break;
	}

	if (command.type == CMD::DROP)
		this->_handleDrop();

	if (!command.silent)
		this->_notify();
}

void Game::_handleDrop(void)
{
	++this->_board._numBlockSinceClear;
	// put next block on the board
	this->_board.insertCurrentBlock();
	if (this->_board.setCurrentBlock(this->_board.getNextBlock()) == false) {
		// if a new block cannot be added, the game is over
		this->_updateScore();
		this->restart();
		std::cerr << "Game Over!\n";
		return;
	}
	this->_board.setNextBlock(this->_level->getNextBlock());

	if(this->_board._currentBlock->getType() == BlockType::D) {
		this->_board.drop();
		this->_handleDrop();
	}
}

void Game::launch(void)
{
	auto firstBlock = this->_level->getNextBlock();
	auto nextBlock = this->_level->getNextBlock();
	if (this->_board.setCurrentBlock(firstBlock) == false) {
		std::cerr << "could not add first block\n";
	}
	this->_board.setNextBlock(nextBlock);
	this->_notify();
}

void Game::restart(void)
{
	std::cerr << "restarting\n";
	// reset the board
	this->_board.reset();

	// reset the level
	this->_level->closeSequence();

	// guarentee that EOF bit is reset
	std::shared_ptr<std::ifstream> fs = std::make_shared<std::ifstream>();
	this->_level = LevelFactory::createLevel(this->_startLevel,
	                                         this->_defaultSequence,
	                                         this,
	                                         true,
	                                         fs);

	if (this->_board.setCurrentBlock(this->_level->getNextBlock()) == false) {
		std::cerr << "could not add first block\n";
	}
	this->_board.setNextBlock(this->_level->getNextBlock());
}

bool Game::isRunning(void) const
{
	return this->_running;
}

void Game::_updateScore(void)
{
	// TODO: implement
}

int Game::getNumBlocksSinceClear(void)
{
	return this->_board._numBlockSinceClear;
}

void Game::levelup(void)
{
	if (this->_level->getLevel() < 4) {
		int newLevel = this->_level->_level + 1;
		this->_level = LevelFactory::createLevel(newLevel,
		                                         _level->_filePath,
		                                         this,
		                                         _level->_random,
		                                         _level->_sequence);
	}
	// std::cerr << "Level UP to : " << this->_level->_level << "\n";
}

void Game::leveldown(void)
{
	if (this->_level->getLevel() > 0) {
		int newLevel = this->_level->_level - 1;
		this->_level = LevelFactory::createLevel(newLevel,
		                                         _level->_filePath,
		                                         this,
		                                         _level->_random,
		                                         _level->_sequence);
	}
	// std::cerr << "Level D./OWN to : " << this->_level->_level << "\n";
}
