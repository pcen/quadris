#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <queue>
#include <string>
#include <mutex>
#include "../game/Game.h"
#include "Command.h"

class Controller
{
public:
	Controller(Game& game);

	void push(Command command);
	void push(const std::string& command);
	void send_commands(void);

private:
	std::mutex _lock;
	Game& _game;
	std::queue<Command> _command_queue;

};

#endif // CONTROLLER_H
