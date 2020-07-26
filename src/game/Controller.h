#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <queue>
#include <vector>
#include <string>
#include <mutex>

#include "Game.h"
#include "Command.h"

class Controller
{
public:
	Controller(Game& game);

	void push(Command command);
	void push(std::vector<Command> commands);
	void send_commands(void);

private:
	void _buildTrie();
	std::vector<Command> _processCommand(const std::string& command) const;
	std::mutex _lock;
	Game& _game;
	std::queue<Command> _command_queue;
};

#endif // CONTROLLER_H
