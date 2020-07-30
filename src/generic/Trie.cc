#include "Trie.h"

#include <iostream>

TrieNode::TrieNode(char value, CommandType type, std::string command)
	: value{value}, type{type}, command{command}, frequency{1}
{

}

TrieNodeRef TrieNode::at(char child)
{
	if (this->is_child(child))
		return this->children[child];
	else
		return nullptr;
}

void TrieNode::add_child(char child, CommandType type, std::string command)
{
	if (!this->is_child(child))
		this->children[child] = std::make_shared<TrieNode>(child, type, command);
}

bool TrieNode::is_child(char child)
{
	return this->children.find(child) != this->children.end();
}

// Trie Implementation

Trie::Trie()
	: _root{ std::make_unique<TrieNode>('\0', CommandType::UNDEFINED_COMMAND, "") }
{

}

Trie::~Trie()
{

}

void Trie::push(const std::string& value, CommandType command)
{
	TrieNodeRef node = this->_root;
	for (unsigned int i = 0; i < value.length(); i++) {
		while (node->is_child(value.at(i))) {
			node = node->at(value.at(i++));
			node->frequency++;
		}

		node->add_child(value.at(i), command, value);
		node = node->at(value.at(i));
	}

	node->is_end_of_word = true;
}

Command Trie::findShortestPrefix(const std::string& value) {
	TrieNodeRef node = this->_root;
	
	unsigned int i = 0;

	Command matched;	

	while (i < value.size() && node->is_child(value.at(i))) {
		node = node->at(value.at(i++));

		if (node->frequency == 1) { // found unique path
			matched = Command(node->command, node->type);
		}
	}
	
	// check to see if the rest of the command is valid
	if (matched.type != CommandType::UNDEFINED_COMMAND && matched.message.rfind(value, 0) == 0) {
		return matched;
	}

	return Command(); //default command
}

bool Trie::search(const std::string& value) {
	TrieNodeRef node = this->_root;
	
	unsigned int i = 0;
	while (i < value.size()) {
		if (!node->is_child(value.at(i))) {
			return false;
		}
		node = node->at(value.at(i++));
	}

	return node->is_end_of_word;
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
