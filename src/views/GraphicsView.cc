#include "GraphicsView.h"

#include <iostream>

#include "../game/Command.h"

GraphicsView::GraphicsView(const std::string& name, Game* game, Controller* controller, int argc, char** argv)
	: View{ game, controller }, _open{ false }, _name{ name },
	_app(argc, argv), _window{ name }
{
	this->_window.open();
	this->_open = true;
}

void GraphicsView::notify(void) const
{
	std::cerr << "GraphicsView::notify\n";
	if (this->_game != nullptr || !this->_game->isRunning()) {
		// TODO: GraphicsView should shut down here, but notify is const
		// this->_shutdown();
	}
}

void GraphicsView::pollInput(void)
{
	this->_app.processEvents();

	// user closed graphics view
	if (!this->_window.isOpen()) {
		this->_shutdown();

		// quit game
		this->_controller->push(Command(CMD::QUIT));
	}

	this->_window.render();
}

void GraphicsView::_shutdown(void)
{
	// unsubscribing stops game from notifying view
	if (this->_game)
		this->_game->unsubscribe(this);
	this->_subscribed = false;

	// closing stops view manager letting view respond to input
	this->_open = false;
}

bool GraphicsView::isOpen(void) const
{
	return this->_open;
}
