#include "CommandInterpreter.h"

typedef std::lock_guard<std::mutex> thread_lock;

CommandInterpreter::CommandInterpreter(Game* game)
	: _game{ game }
{

}

// lock mutex to prevent reading empty while another thread
// is adding a command to the queue, or the queue is being flushed
// - method is non-const since it must lock mutex
bool CommandInterpreter::empty(void)
{
	thread_lock lk(_lock);
	return _command_queue.empty();
}

// lock mutex to prevent writing to queue while another thread
// is adding accessing or modifying the queue
void CommandInterpreter::push(const std::string& command)
{
	thread_lock lk(_lock);
	_command_queue.push(command);
}

// lock mutex to prevent the queue from being accessed while
// a flush is in process
void CommandInterpreter::flush_commands(void)
{
	thread_lock lk(_lock);
	while (!_command_queue.empty()) {
		_game->update(_command_queue.front());
		_command_queue.pop();
	}
}
