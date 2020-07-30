#include "GraphicsView.h"

#include "../controller/Command.h"

#include <unordered_map>

// TODO: read mappings from file
static const std::unordered_map<std::string, CommandType> buttonCommandMap =
{
	{"left", CMD::LEFT}, {"right", CMD::RIGHT}, {"drop", CMD::DROP},
	{"down", CMD::DOWN}, {"clockwise", CMD::CLOCKWISE},
	{"counter clockwise", CMD::COUNTERCLOCKWISE},
	{"level up", CMD::LEVELUP}, {"level down", CMD::LEVELDOWN},
	{"restart", CMD::RESTART}, {"hint", CMD::HINT}
};

// 65 = A key
// 83 = S key
// 68 = D key
// 16777234 = left arrow key
// 16777236 = right arrow key
// 32 = space key
static const std::unordered_map<int, CommandType> keyCommandMap = {
	{65, CMD::LEFT}, {83, CMD::DOWN}, {68, CMD::RIGHT},
	{16777234, CMD::COUNTERCLOCKWISE}, {16777234, CMD::CLOCKWISE},
	{32, CMD::DROP}
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
		if (buttonCommandMap.find(input) != buttonCommandMap.end())
			this->_controller->push(Command(buttonCommandMap.at(input)));
	}

	// process keyboard input
	std::vector<int> keyboardInput = this->_window.getKeyboardInput();
	for (auto& input : keyboardInput) {
		// if the keyboard input is a valid command, send it to the controller
		if (keyCommandMap.find(input) != keyCommandMap.end())
			this->_controller->push(Command(keyCommandMap.at(input)));
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
