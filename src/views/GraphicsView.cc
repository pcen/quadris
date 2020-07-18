#include "GraphicsView.h"

#include <iostream>

GraphicsView::GraphicsView(const std::string& name, Game* game)
	: View{ game }
{
	_window = std::make_unique<X11Window>(name);
}

void GraphicsView::update(void) const
{
	std::cerr << "GraphicsView::update\n";
	if (!_game->is_running())
		_window->close();
}

std::future<void> GraphicsView::start(void)
{
	return std::async(std::launch::async, [&](){
		_window->start();
		// if the window is closed while the game is still being
		// played, unsubscribe from the game
		_game->unsubscribe(this);
		return;
	});
}
