#include "GraphicsView.h"

#include <iostream>

#include "../controller/Command.h"

GraphicsView::GraphicsView(const std::string& name, Game* game, CommandInterpreter* interpreter, int argc, char** argv)
	: View{ game, interpreter }, _open{ false }, _name{ name },
	_app(argc, argv), _window{ name }
{
	_window.open();
	this->_open = true;
}

void GraphicsView::notify(void) const
{
	std::cerr << "GraphicsView::notify\n";
	if (this->_game != nullptr || !this->_game->is_running()) {
		// TODO: GraphicsView should shut down here, but notify is const
		// this->_shutdown();
	}
}

void GraphicsView::poll_input(void)
{
	_app.processEvents();

	// user closed graphics view
	if (!_window.isOpen()) {
		this->_shutdown();

		// quit game
		Command c(CommandType::QUIT);
		_interpreter->push(c);
	}
}

void GraphicsView::_shutdown(void)
{
	// unsubscribing stops game from notifying view
	if (this->_game)
		this->_game->unsubscribe(this);
	// closing stops view manager letting view respond to input
	this->_open = false;
}

bool GraphicsView::isOpen(void) const
{
	return _open;
}
