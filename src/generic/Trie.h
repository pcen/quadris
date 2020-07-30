#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>
#include <memory>

#include "../controller/Command.h"

class TrieNode
{
	friend class Trie;

public:
	TrieNode(char value, CommandType type, std::string command);

private:
	// data
	char value;
	CommandType type;
	std::string command;

	int frequency;
	bool is_end_of_word;

	std::shared_ptr<TrieNode> at(char child);
	void add_child(char child, CommandType command, std::string s);
	bool is_child(char child);

	std::unordered_map<char, std::shared_ptr<TrieNode>> children;
};

typedef std::shared_ptr<TrieNode> TrieNodeRef;

class Trie
{
public:
	Trie();
	~Trie();

	void push(const std::string& value, CommandType command);
	Command findShortestPrefix(const std::string& value);
	bool search(const std::string& value);
	void print(void);

private:
	void _print(TrieNodeRef node);
	TrieNodeRef _root;

};

#endif // TRIE_H
