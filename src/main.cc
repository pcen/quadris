#include <iostream>
#include <future>
#include <thread>

#include "window/X11Window.h"
#include "generic/Trie.h"
#include "game/Game.h"

void poll_console(Game* game)
{
	std::string cmd;
	while (game->is_running()) {
		std::cin >> cmd;
		game->update(cmd);
	}
}

class ConsoleView
{
public:
	Game* _game;

	ConsoleView(Game* game) : _game{ game } {}

	std::future<void> start()
	{
		return std::async(std::launch::async, [&](){
			return poll_console(_game);
		});
	}
};

int main(int argc, char* argv[])
{
	Game game;
	ConsoleView cv(&game);

	std::string flag1;
	if (argc > 1)
		flag1 = argv[1];
	else
		flag1 = "\0";

	auto thread1 = cv.start();

	X11Window window("Quadris");
	// TODO: window should be notified when game is done running,
	// currently window will remain open even when game quits
	window.start();

	return 0;
}
