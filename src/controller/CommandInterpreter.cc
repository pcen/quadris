#include "CommandInterpreter.h"

CommandInterpreter::CommandInterpreter(Game* game)
	: _game{ game }
{

}

bool CommandInterpreter::empty(void) const
{
	return _command_queue.empty();
}

void CommandInterpreter::push(const std::string& command)
{
	_command_queue.push(command);
}

// TODO: this is not thread safe
void CommandInterpreter::flush_commands(void)
{
	while (!_command_queue.empty()) {
		_game->update(_command_queue.front());
		_command_queue.pop();
	}
}
