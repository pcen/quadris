#include "Controller.h"
#include <fstream>
#include <iostream>

typedef std::lock_guard<std::mutex> thread_lock;

Controller::Controller(Game& game)
	: _game{ game }
{
	_trie = new Trie();
	this->_buildTrie();
}

void Controller::_buildTrie() {
	std::ifstream infile("./src/controller/commands.txt");

	std::string command;
	int id;
	while (infile >> command >> id)
	{
		_trie->push(command, (CommandType) id);
	}
}

// lock mutex to prevent writing to queue while another thread
// is adding accessing or modifying the queue
void Controller::push(Command command)
{
	thread_lock lk(_lock);
	_command_queue.push(command);
}

void Controller::push(const std::string& command)
{
	thread_lock lk(_lock);

	std::vector<Command> commands = this->_processCommand(command);
	// TODO: throw exception

	for (auto c: commands) {
		std::cout << c.message << std::endl;
		_command_queue.push(c);
	}
}

// lock mutex to prevent the queue from being accessed while
// a flush is in process
void Controller::send_commands(void)
{
	thread_lock lk(_lock);
	while (!_command_queue.empty()) {
		_game.update(_command_queue.front());
		_command_queue.pop();
	}
}

std::vector<Command> Controller::_processCommand(const std::string& s) const
{
	std::vector<Command> commands;

	unsigned int split = 0;

	for (; split < s.length(); split++) {
		char c = s[split];
		if (c > '9' || c < '0')
			break;
	}

	std::string multiplierString = s.substr(0, split);
	int multiplier = multiplierString.length() ? std::stoi(multiplierString) : 1;
  std::string command = s.substr(split);

	Command c = Command(command, _trie->findShortestPrefix(command));

	if (c.type != CommandType::UNDEFINED_COMMAND && _trie->search(command)) {
		for (int i = 0; i < multiplier; i++) {
			commands.push_back(c);
		}
	}

	return commands;
}