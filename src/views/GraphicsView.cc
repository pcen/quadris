#include "GraphicsView.h"

#include <iostream>

GraphicsView::GraphicsView(const std::string& name, Game* game)
	: View{ game }
{
	_window = std::make_unique<X11Window>("Quadris");
}

void GraphicsView::update(void) const
{
	std::cerr << "GraphicsView::update\n";
	if (!_game->is_running()) {
		// terminate window's thread:
		std::cerr << "Closing window...\n";
		_window->close();
	}
}

std::future<void> GraphicsView::start(void)
{
	return std::async(std::launch::async, [&](){
		return _window->start();
	});
}
