#include "GraphicsView.h"

#include <iostream>

GraphicsView::GraphicsView(const std::string& name, Game* game)
	: View{ game }
{
	_window = std::make_unique<X11Window>(name);
}

void GraphicsView::notify(void) const
{
	std::cerr << "GraphicsView::notify\n";
	std::cerr << "Thread ID: " << get_thread_id() << "\n";
	if (!_game->is_running())
		_window->close();
}

void GraphicsView::start(void)
{
	_window->start();
	// if the window is closed while the game is still being
	// played, unsubscribe from the game
	_game->unsubscribe(this);
}

std::future<void> GraphicsView::create(const std::string& name, Game* game)
{
	return std::async(std::launch::async, [name, game](){
		GraphicsView gv(name, game);
		std::cerr << "graphics view thread: " << gv.get_thread_id() << "\n";
		gv.start();
		std::cerr << "graphics view thread closed\n";
	});
}
