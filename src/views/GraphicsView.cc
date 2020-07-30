#include "GraphicsView.h"

#include "../controller/Command.h"

#include <iostream>
#include <unordered_map>

static const std::unordered_map<std::string, CommandType> commandMap =
{
	{"left", CMD::LEFT}, {"right", CMD::RIGHT}, {"drop", CMD::DROP},
	{"down", CMD::DOWN}, {"clockwise", CMD::CLOCKWISE},
	{"counter clockwise", CMD::COUNTERCLOCKWISE},
	{"level up", CMD::LEVELUP}, {"level down", CMD::LEVELDOWN},
	{"restart", CMD::RESTART}, {"hint", CMD::HINT}
};

GraphicsView::GraphicsView(const std::string& name, Game* game, Controller* controller, int argc, char** argv)
	: View{ game, controller }, _open{ false }, _name{ name },
	_app(argc, argv), _window{ name }
{
	this->_window.open();
	this->_open = true;
}

void GraphicsView::notify(void) const
{
	if (this->_game != nullptr || !this->_game->isRunning()) {
		// TODO: GraphicsView should shut down here, but notify is const
		// this->_shutdown();
	}
}

void GraphicsView::pollInput(void)
{
	// process Qt events
	this->_app.processEvents();

	// process window button input
	std::vector<std::string> buttonInput = this->_window.getButtonInput();
	for (auto& input : buttonInput) {
		// if the button input is a valid command, send it to the controller
		if (commandMap.find(input) != commandMap.end())
			this->_controller->push(Command(commandMap.at(input)));
	}

	// user closed graphics view
	if (!this->_window.isOpen())
		this->_shutdown();

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
