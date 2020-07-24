#include "Controller.h"

typedef std::lock_guard<std::mutex> thread_lock;

Controller::Controller(Game& game)
	: _game{ game }
{

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

	Command c;

	// TODO: interpret text command using Trie
	if (command == "quit")
		c.type = CMD::QUIT;

	_command_queue.push(c);
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
