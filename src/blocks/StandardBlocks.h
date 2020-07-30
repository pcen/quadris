#ifndef STANDARDBLOCKS_H
#define STANDARDBLOCKS_H

#include "Block.h"

class IBlock : public Block
{
public:
	IBlock(int);

private:
	friend class BlockFactoryInitializer;
	class Factory;
	friend class Factory;

	class Factory : public BlockFactory
	{
		public:
			std::shared_ptr<Block> create(int level) {
				return std::make_shared<IBlock>(level);
			};
			friend class BlockFactoryInitializer;
	};
};

class JBlock : public Block
{
public:
	JBlock(int);

private:
	friend class BlockFactoryInitializer;
	class Factory;
	friend class Factory;

	class Factory : public BlockFactory
	{
		public:
			std::shared_ptr<Block> create(int level) {
				return std::make_shared<JBlock>(level);
			};
			friend class BlockFactoryInitializer;
	};
};

class LBlock : public Block
{
public:
	LBlock(int);

private:
	friend class BlockFactoryInitializer;
	class Factory;
	friend class Factory;

	class Factory : public BlockFactory
	{
		public:
			std::shared_ptr<Block> create(int level) {
				return std::make_shared<LBlock>(level);
			};
			friend class BlockFactoryInitializer;
	};
};

class OBlock : public Block
{
public:
	OBlock(int);

private:
	friend class BlockFactoryInitializer;
	class Factory;
	friend class Factory;

	class Factory : public BlockFactory
	{
		public:
			std::shared_ptr<Block> create(int level) {
				return std::make_shared<OBlock>(level);
			};
			friend class BlockFactoryInitializer;
	};
};

class SBlock : public Block
{
public:
	SBlock(int);

private:
	friend class BlockFactoryInitializer;
	class Factory;
	friend class Factory;

	class Factory : public BlockFactory
	{
		public:
			std::shared_ptr<Block> create(int level) {
				return std::make_shared<SBlock>(level);
			};
			friend class BlockFactoryInitializer;
	};
};

class ZBlock : public Block
{
public:
	ZBlock(int);

private:
	friend class BlockFactoryInitializer;
	class Factory;
	friend class Factory;

	class Factory : public BlockFactory
	{
		public:
			std::shared_ptr<Block> create(int level) {
				return std::make_shared<ZBlock>(level);
			};
			friend class BlockFactoryInitializer;
	};
};

class TBlock : public Block
{
public:
	TBlock(int);

private:
	friend class BlockFactoryInitializer;
	class Factory;
	friend class Factory;

	class Factory : public BlockFactory
	{
		public:
			std::shared_ptr<Block> create(int level) {
				return std::make_shared<TBlock>(level);
			};
			friend class BlockFactoryInitializer;
	};
};

#endif // STANDARDBLOCKS_H
