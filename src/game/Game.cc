#include "Game.h"

#include <iostream>
#include <string>

#include "./blocks/StandardBlocks.h"
Game::Game(uint startLevel, std::string filePath)
	: _board("./assets/_.png"), _startSequence{ filePath }, _running{true},
	_score{0}, _highScore{0}, _startLevel{startLevel}
{
	std::shared_ptr<std::ifstream> fs = std::make_shared<std::ifstream>();
	this->_level = LevelFactory::createLevel(startLevel, filePath, this, true, fs);
	this->_level->openSequence(this->_startSequence);
}

Game::~Game()
{
	this->_level->closeSequence();
}

const Board& Game::getBoard(void) const
{
	return this->_board;
}

void Game::update(const Command& command)
{
	bool rotate = false;
	bool translate = false;

	switch(command.type) {
		case CMD::QUIT:
			this->_running = false;
			break;

		case CMD::CLOCKWISE:
		case CMD::COUNTERCLOCKWISE:
			this->_board.rotate(command.type == CMD::CLOCKWISE);
			rotate = true;
			break;

		case CMD::DOWN:
			this->_board.translate(Direction::DOWN);
			translate = true;
			break;

		case CMD::LEFT:
			this->_board.translate(Direction::LEFT);
			translate = true;
			break;

		case CMD::RIGHT:
			this->_board.translate(Direction::RIGHT);
			translate = true;
			break;

		case CMD::DROP:
			this->_board.drop();
			break;

		case CMD::RESTART:
			this->restart();
			break;

		case CMD::LEVELUP:
		case CMD::LEVELDOWN:
			this->_changeLevel(command.type == CMD::LEVELUP);
			break;

		// random block generation (sequence file remains unchanged)
		case CMD::RANDOM:
			this->_level->useRandom(true);
			break;

		// non-random block generation from the specified sequence file
		case CMD::NORANDOM_FILE:
			// ignore when level number is less than 3
			if (this->_level->getLevel() < 3)
				break;
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

	// down heavy blocks by 1 cell
	if (!command.silent && (rotate || translate)) {
		if (this->_board.getCurrentBlock()->isHeavy())
			this->_board.translate(Direction::DOWN);
	}

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

	if (this->_board._currentBlock->getType() == BlockType::D) {
		this->_board.drop();
		this->_handleDrop();
	}
}

void Game::launch(void)
{
	if (this->_board.setCurrentBlock(this->_level->getNextBlock()) == false) {
		std::cerr << "could not add first block\n";
	}
	this->_board.setNextBlock(this->_level->getNextBlock());
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
	                                         this->_startSequence,
	                                         this,
	                                         true,
	                                         fs);

	this->_level->openSequence(this->_startSequence);

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

void Game::_changeLevel(bool up)
{
	int levelNum = this->_level->getLevel();
	if ((up && levelNum < MAX_LEVEL) || (!up && levelNum > 0)) {
		int newLevel = levelNum + (up ? 1 : -1);
		this->_level = LevelFactory::createLevel(newLevel,
		                                         _level->_filePath,
		                                         this,
		                                         _level->_random,
		                                         _level->_sequence);

		// save the next block for this level
		// if (!this->_level->isRandom()) {
		// 	this->_nextBlocks[levelNum] = this->_board.getNextBlock();
		// }
		// if (this->_nextBlocks.has(this->_level->getLevel())) {
		// 	// check if there is a cached next block
		// 	this->_board.setNextBlock(this->_nextBlocks.at(this->_level->getLevel()));
		// } else {
		// 	// otherwise, generate a new next block for the new level
		this->_board.setNextBlock(this->_level->getNextBlock());
		// }

	}
}

unsigned int Game::getScore(void) const
{
	return this->_score;
}

unsigned int Game::getHighScore(void) const
{
	return this->_highScore;
}

int Game::getLevel(void) const
{
	return this->_level->getLevel();
}
