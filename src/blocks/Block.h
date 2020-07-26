#ifndef BLOCK_H
#define BLOCK_H

#include "Cell.h"

#include <vector>
#include <memory>

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

#include <vector>
#include <memory>

enum class BlockType{
	I = 'I',
	J = 'J',
	L = 'L',
	O = 'O',
	S = 'S',
	Z = 'Z',
	T = 'T'
};

class Block : public std::enable_shared_from_this<Block>
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


class BlockFactoryInitializer;


class BlockFactory
{
public:
	virtual ~BlockFactory() {};
	friend class BlockFactoryInitializer;

	static std::shared_ptr<Block> createBlock(const std::string&, int);

private:
	static std::map<std::string, std::unique_ptr<BlockFactory>> _factories;
	virtual std::shared_ptr<Block> create(int) = 0;
};



class BlockFactoryInitializer
{
private:
	static BlockFactoryInitializer si;

	BlockFactoryInitializer();
	~BlockFactoryInitializer() {};
};



#endif // BLOCK_H
