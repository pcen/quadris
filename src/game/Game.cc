#include "Game.h"

#include <iostream>
#include <string>
#include <cmath>

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

void Game::_setNextBlock(void)
{
	int level = this->_level->getLevel();
	std::shared_ptr<Block> nextBlock = this->_level->getNextBlock(level);
	this->_board.setNextBlock(nextBlock);
	this->_prevLevelBlocks[level] = nextBlock;
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
			// ignore when level number is less than 3 or already random
			if (this->_level->getLevel() < 3 || this->_level->_random)
				break;
			this->_level->useRandom(true);
			this->_setNextBlock();
			break;

		// non-random block generation from the specified sequence file
		case CMD::NORANDOM_FILE:
			// ignore when level number is less than 3
			if (this->_level->getLevel() < 3)
				break;
			this->_level->openSequence(command.message);
			this->_level->useRandom(false);
			this->_setNextBlock();
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
	int rowsCleared = this->_board.insertCurrentBlock();
	if (rowsCleared > 0) {
		this->_updateScore(rowsCleared);
		this->_board._numBlockSinceClear = 0;
	}

	if (this->_board.setCurrentBlock(this->_board.getNextBlock()) == false) {
		// if a new block cannot be added, the game is over
		this->restart();
		std::cerr << "Game Over!\n";
		return;
	}
	this->_setNextBlock();

	if (this->_board._currentBlock->getType() == BlockType::D) {
		this->_board.drop();
		this->_handleDrop();
	}
}

void Game::launch(void)
{
	if (this->_board.setCurrentBlock(this->_level->getNextBlock(this->_level->getLevel())) == false) {
		std::cerr << "could not add first block\n";
	}
	this->_setNextBlock();
	this->_notify();
}

void Game::restart(void)
{
	// reset the board
	this->_board.reset();

	// reset the score and set the highscore
	this->_highScore = std::max(this->_highScore, this->_score);
	this->_score = 0;

	// reset the level
	this->_level->closeSequence();

	// guarantee that EOF bit is reset
	std::shared_ptr<std::ifstream> fs = std::make_shared<std::ifstream>();
	this->_level = LevelFactory::createLevel(this->_startLevel,
	                                         this->_startSequence,
	                                         this,
	                                         true,
	                                         fs);

	this->_level->openSequence(this->_startSequence);

	this->_prevLevelBlocks.clear();

	if (this->_board.setCurrentBlock(this->_level->getNextBlock(this->_level->getLevel())) == false) {
		std::cerr << "could not add first block\n";
	}
	this->_setNextBlock();
}

bool Game::isRunning(void) const
{
	return this->_running;
}

void Game::_updateScore(int rowsCleared)
{
	int rowClearPoints = std::pow(this->_level->getLevel() + rowsCleared, 2);
	int blocksClearedPoints = 0;
	auto blocks = this->_board.getBlocks();
	for (auto b = blocks.begin(); b != blocks.end();) {
		Block* block = b->get();
		if (block->isCleared()) {
			blocksClearedPoints += std::pow(block->getLevelGenerated() + 1, 2);
			b = blocks.erase(b);
		} else {
			++b;
		}
	}
	this->_score += rowClearPoints + blocksClearedPoints;
}

int Game::getNumBlocksSinceClear(void)
{
	return this->_board._numBlockSinceClear;
}

void Game::_setBlockFromCache(int prevLevel)
{
	int level = this->_level->getLevel();
	// In the case that we are in sequenced mode
	if (!this->_level->_random) {
		// To switch to sequenced mode we must have gone to level 3 or 4at some point
		// to get from level 3 or 4 to level 0 we must have gone through level 3
		if (level == 0) {
			// Find the sequenced cache block from level3 and set the next block to it
			std::shared_ptr<Block> prevSequenceBlock = this->_prevLevelBlocks[3];
			this->_prevLevelBlocks[0] = prevSequenceBlock;
			this->_board._nextBlock = prevSequenceBlock;
			// If we have not reached the end of our file then we want to also
			// make sure the next block has the correct properties for level 0 blocks
			if (this->_board._nextBlock != nullptr) {
				this->_board._nextBlock->_levelGenerated = 0;
				this->_board._nextBlock->_isHeavy = false;
			}
		}
		// If we are switching from level 3 to level 4 in sequenced mode
		if (level == 4 && prevLevel == 3) {
			// Set the next block of level 4 to the cached block from level 3
			this->_prevLevelBlocks[4] = this->_prevLevelBlocks[3];
			if (this->_board._nextBlock != nullptr)
				// if we have not depleted sequence.txt then update the next block's level
				this->_board._nextBlock->_levelGenerated = 4;
			return;
		}
		if (level == 3) {
			// If we are switching from level 4 to level 3 in sequenced mode
			if (prevLevel == 4) {
				// Set the next block to the cached block from level 4
				this->_prevLevelBlocks[3] = this->_prevLevelBlocks[4];
				if (this->_board._nextBlock != nullptr)
					// if we have not depleted sequence.txt then update the next block's level
					this->_board._nextBlock->_levelGenerated = 3;
				return;
			}
			// Otherwise we have switched from a lower level back to 3 in sequenced mode
			else {
				// Level 0 will use the same sequence file so if we have used it in level0
				// before switching back, we must have the next block in the sequence cached
				if (this->_prevLevelBlocks.find(0) != this->_prevLevelBlocks.end()) {
					// Set the nextblock and level3's cached block to also be this block
					std::shared_ptr<Block> prevSequenceBlock = this->_prevLevelBlocks[0];
					this->_prevLevelBlocks[3] = prevSequenceBlock;
					this->_board._nextBlock = prevSequenceBlock;
					if (this->_board._nextBlock != nullptr) {
						// If we have not depleted sequence.txt update the block's properties
						this->_board._nextBlock->_levelGenerated = 3;
						this->_board._nextBlock->_isHeavy = true;
					}
				}
			}
		}
	}

	// Check if we have a cached nextBlock from a previous switch to the level
	// and set the next block back to it if we do
	auto cacheLoc = this->_prevLevelBlocks.find(level);
	if (cacheLoc != this->_prevLevelBlocks.end()) {
		this->_board._nextBlock = (*cacheLoc).second;
		// If we have switched to level 3 or 4, but previously were in norandom/sequenced
		// mode, then we want to check if the cached block is empty due to having depleted
		// the sequence.txt file, in which case we want to generate a new block
		if (level == 3 || level == 4) {
			if (this->_level->_random && this->_board._nextBlock == nullptr)
				this->_setNextBlock();
		}
	}
	else
		// Otherwise we generate a new block entirely
		this->_setNextBlock();
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
		
		this->_setBlockFromCache(levelNum);
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
