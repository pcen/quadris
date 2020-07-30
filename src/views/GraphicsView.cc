#include "GraphicsView.h"

#include <iostream>
#include <unordered_map>

#include "../controller/Command.h"

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

// prevent QtWarningMsg from writing to console and ruining
// ConsoleView's display
void messageHandler(QtMsgType type,
                    const QMessageLogContext &context,
                    const QString &msg)
{
	switch (type) {
		case QtDebugMsg:
		case QtInfoMsg:
		case QtWarningMsg:
			break;
		case QtCriticalMsg:
		case QtFatalMsg:
		default:
			std::string message = msg.toStdString();
			std::cerr << "Qt ERROR: " << message
			          << " (" << context.file << ": " << context.line
			          << ", " << context.function << ")\n";
			break;
	}
}

GraphicsView::GraphicsView(const std::string& name, Game* game, Controller* controller)
	: View{ game, controller }, _qtArgCount{ 0 }, _qtArgs{ nullptr },
	_open{ false }, _name{ name },
	_app(_qtArgCount, _qtArgs), _window{ name, game }
{
	qInstallMessageHandler(messageHandler);
	this->_window.open();
	this->_open = true;
}

void GraphicsView::update(void)
{
	if (this->_game == nullptr || !this->_game->isRunning()) {
		this->_shutdown();
	}

	this->_window.render();
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
