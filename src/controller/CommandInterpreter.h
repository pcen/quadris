#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H

#include <queue>
#include <string>
#include <mutex>
#include "../game/Game.h"

class CommandInterpreter
{
public:
	CommandInterpreter(Game* game);

	bool empty(void) const;

	void push(const std::string& command);
	void flush_commands(void);

private:
	std::mutex _lock;
	Game* _game;
	std::queue<std::string> _command_queue;

};

#endif // COMMANDINTERPRETER_H
