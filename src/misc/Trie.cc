#include "Trie.h"

#include <iostream>

TrieNode::TrieNode(char value)
	: value{ value }
{

}

TrieNodeRef TrieNode::at(char child)
{
	if (this->is_child(child))
		return this->children[child];
	else
		return nullptr;
}

void TrieNode::add_child(char child)
{
	if (!this->is_child(child))
		this->children[child] = std::make_shared<TrieNode>(child);
}

bool TrieNode::is_child(char child)
{
	return this->children.find(child) != this->children.end();
}

// Trie Implementation

Trie::Trie()
	: _root{ std::make_unique<TrieNode>('\0') }
{

}

Trie::~Trie()
{

}

void Trie::push(const std::string& value)
{
	TrieNodeRef node = this->_root;
	for (unsigned int i = 0; i < value.length(); i++) {
		while (node->is_child(value.at(i)))
			node = node->at(value.at(i++));

		node->add_child(value.at(i));
		node = node->at(value.at(i));
	}
}

void Trie::print(void)
{
	this->_print(this->_root);
}

void Trie::_print(TrieNodeRef node)
{
	std::cout << node->value;
	for (auto& n: node->children) {
		this->_print(n.second);
		if (node->value == '\0' && node->children.size() > 1)
			std::cout << '\n';
	}
}
