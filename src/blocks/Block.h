#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <memory>
#include <map>

#include "Cell.h"
class Cell;

enum class BlockType : char {
	I = 'I',
	J = 'J',
	L = 'L',
	O = 'O',
	S = 'S',
	Z = 'Z',
	T = 'T',
	EMPTY = '.'
};

class Block
{
public:
	virtual ~Block() {};

	BlockType getType(void);

protected:
	BlockType _type;
	Coord _bottomLeft;
	std::vector<std::shared_ptr<Cell>> _cells;

	int _levelGenerated;
	bool _isHeavy;

};

class BlockFactoryInitializer
{
private:
	static BlockFactoryInitializer si;

	BlockFactoryInitializer();
	~BlockFactoryInitializer() {};
};

class BlockFactory;

class BlockFactory
{
	friend class BlockFactoryInitializer;
public:
	virtual ~BlockFactory() {};

	static std::shared_ptr<Block> createBlock(const std::string&, int);

private:
	static std::map<std::string, std::unique_ptr<BlockFactory>> _factories;
	virtual std::shared_ptr<Block> create(int) = 0;
};

#endif // BLOCK_H
