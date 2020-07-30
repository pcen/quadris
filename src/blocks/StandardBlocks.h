#ifndef STANDARDBLOCKS_H
#define STANDARDBLOCKS_H

#include "Block.h"

class IBlock : public Block
{
	void _rotate(bool) override;
};

class JBlock : public Block
{
	void _rotate(bool) override;
};

class LBlock : public Block
{
	void _rotate(bool) override;
};

class OBlock : public Block
{
	void _rotate(bool) override;
};

class SBlock : public Block
{
	void _rotate(bool) override;
};

class ZBlock : public Block
{
	void _rotate(bool) override;
};

class TBlock : public Block
{
	void _rotate(bool) override;
};

#endif // STANDARDBLOCKS_H
