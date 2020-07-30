#ifndef STANDARDLEVELS_H
#define STANDARDLEVELS_H

#include <map>

#include "Level.h"


class Level0 : public Level
{
public:
	Level0(std::string, Game*, bool);
	std::shared_ptr<Block> getNextBlock(void) const override;
};


class Level1 : public Level
{
public:
	Level1(std::string, Game*, bool);
	std::shared_ptr<Block> getNextBlock(void) const override;
};


class Level2 : public Level
{
public:
	Level2(std::string, Game*, bool);
	std::shared_ptr<Block> getNextBlock(void) const override;
};


class Level3 : public Level
{
public:
	Level3(std::string, Game*, bool);
	virtual std::shared_ptr<Block> getNextBlock(void) const override;
};


class Level4 : public Level3
{
public:
	Level4(std::string, Game*, bool, std::shared_ptr<Level3>);
	std::shared_ptr<Block> getNextBlock(void) const override;
private:
	std::shared_ptr<Level3> _level3;
};

#endif // STANDARDLEVELS_H
