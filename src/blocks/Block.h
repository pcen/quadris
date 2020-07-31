#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include <memory>
#include <map>

// 2D Coordinate
struct Coord
{
	int _x;
	int _y;

	Coord() {};
	Coord(unsigned int x, unsigned int y) : _x{ x }, _y{ y } {}
	Coord(int x, int y) : _x{ x }, _y{ y } {}

	Coord invert(void);
};

// Coordinate operators
Coord operator+(Coord a, Coord b);
Coord operator-(Coord a, Coord b);

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

// Blocks are comprised of multiple cells
class Cell
{
public:
	Cell(int x, int y, std::string png, bool isDeleted, BlockType type);

	std::string getSprite(void);
	Coord getCoord(void) const;
	int get_x(void);
	int get_y(void);
	char getToken(void) const;
	BlockType getType(void) const;

private:
	friend class Board;

	Coord _coords;
	BlockType _type;
	std::string _sprite;
	bool _isDeleted;
};

class Block
{
public:
	virtual ~Block() {};

	BlockType getType(void);
	std::vector<std::shared_ptr<Cell>>& getCells(void);

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
