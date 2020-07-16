#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>
#include <memory>

class TrieNode
{
	friend class Trie;

public:
	TrieNode(char value);

private:
	char value;
	std::shared_ptr<TrieNode> at(char child);
	void add_child(char child);
	bool is_child(char child);

	std::unordered_map<char, std::shared_ptr<TrieNode>> children;
};

typedef std::shared_ptr<TrieNode> TrieNodeRef;

class Trie
{
public:
	Trie();
	~Trie();

	void push(const std::string& value);
	void print(void);

private:
	void _print(TrieNodeRef node);
	TrieNodeRef _root;

};

#endif // TRIE_H
