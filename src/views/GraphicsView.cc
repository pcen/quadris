#include "GraphicsView.h"

#include <iostream>

GraphicsView::GraphicsView(const std::string& name, Game* game, CommandInterpreter* interpreter, int argc, char** argv)
	: View{ game, interpreter }, _app(argc, argv), _window{ }
{
	_window.show();
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
	_app.processEvents();
}
