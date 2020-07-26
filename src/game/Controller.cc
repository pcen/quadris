#include "Controller.h"

typedef std::lock_guard<std::mutex> thread_lock;

Controller::Controller(Game& game)
	: _game{ game }
{

}

// lock mutex to prevent writing to queue while another thread
// is adding accessing or modifying the queue
void Controller::push(Command c)
{
	thread_lock lk(_lock);

	if (c.type == CommandType::UNDEFINED_COMMAND) 
		return //TODO: throw exception?

	_command_queue.push(c);
}

void Controller::push(std::vector<Command> cs) 
{
	thread_lock lk(_lock);

	for (auto c : cs) {
		if (c.type == CommandType::UNDEFINED_COMMAND)
			continue;

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