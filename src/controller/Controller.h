#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <queue>
#include <string>
#include <mutex>
#include "../game/Game.h"
#include "Command.h"
#include "Trie.h"

class Controller
{
public:
	Controller(Game& game);

	void push(Command command);
	void push(const std::string& command);
	void send_commands(void);

private:
	void _buildTrie();
	std::vector<Command> _processCommand(const std::string& command) const;
	std::mutex _lock;
	Game& _game;
	std::queue<Command> _command_queue;
	Trie* _trie;
};

#endif // CONTROLLER_H
