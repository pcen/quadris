#include "GraphicsView.h"

#include <iostream>

GraphicsView::GraphicsView(const std::string& name, Game* game)
	: View{ game }
{
	_window = std::make_unique<X11Window>(name);
}

void GraphicsView::notify(void) const
{
	std::cerr << "GraphicsView::update\n";
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

std::future<void> GraphicsView::create(Game* game)
{
	return std::async(std::launch::async, [game](){
		std::cerr << "creating graphics view\n";
		GraphicsView graphics_view("Quadris", game);
		graphics_view.start();
		std::cerr << "graphics view thread closed\n";
	});
}
