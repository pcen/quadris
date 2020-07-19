#include "GraphicsView.h"

#include <iostream>

GraphicsView::GraphicsView(const std::string& name, Game* game, CommandInterpreter* interpreter, int argc, char** argv)
	: View{ game, interpreter }, _window{ name, argc, argv }
{

}

void GraphicsView::notify(void) const
{
	std::cerr << "GraphicsView::notify\n";
	if (!_game->is_running()) {
		// _window->close();
		return;
	}
}

void GraphicsView::poll_input(void)
{
	std::cerr << "GraphicsView::poll_event\n";
}

void GraphicsView::start(void)
{
	_window.start();
}
