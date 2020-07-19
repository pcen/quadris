#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H

#include <queue>
#include <string>
#include <mutex>
#include "../game/Game.h"
#include "Command.h"

class CommandInterpreter
{
public:
	CommandInterpreter(Game* game);

	void push(Command command);
	void push(const std::string& command);
	void send_commands(void);

private:
	std::mutex _lock;
	Game* _game;
	std::queue<Command> _command_queue;

};

#endif // COMMANDINTERPRETER_H
