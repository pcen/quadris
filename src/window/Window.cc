#include "Window.h"

#include <QEvent>
#include <QPainter>
#include <QAction>

#define BUTTON_COUNT 10
static const std::string buttonLabels[BUTTON_COUNT] = {
	"left", "right", "down", "drop", "clockwise", "counter clockwise",
	"level up", "level down", "restart", "hint"
};

static const char* buttonStyle =
"font-family: Arial;"
"font-size: 14px;"
"color: rgb(255,255,255);"
"background-color: rgb(64,63,61);"
"min-height: 25px;"
"min-width: 40px;"
"padding-right: 5px;"
"padding-left: 5px;";

Window::Window(const std::string& title, Game* game, QWidget* parent, int width, int height)
	: QMainWindow(parent), _open{ false }, _game{ game }, _buttonPane{ this }
{
	this->setTitle(title);
	this->setSize(width, height);
	this->_initializeButtons();
}

Window::~Window()
{

}

// precondition: _board must be initialized
void Window::_initializeButtons(void)
{
	// set button pane position
	int btnOffset = this->_game->getBoard().getCellSize() * 12;

	this->_buttonPane.move(btnOffset, 0);
	this->_buttonPane.resize(this->_width - btnOffset, this->_height);

	// populate the button pane
	for (auto & label : buttonLabels) {
		QString buttonText = QString::fromStdString(label);
		QButtonPtr b(new QPushButton(buttonText, &this->_buttonPane));
		this->_btns.insert(label, b);
		b->setStyleSheet(buttonStyle);
		// disable selecting buttons with keyboard
		b->setFocusPolicy(Qt::NoFocus);

		// register button callback
		// raw pointer context needed for Qt to manage receiver lifespan
		QPushButton* context = b.data();
		connect(context, &QPushButton::clicked, context, [context, this] {
			if (context != nullptr) {
				std::string command = context->text().toStdString();
				this->_onButtonPress(command);
			}
		});
	}
	this->_positionButtons();
}

// set button positions
// precondition: _btns must be initialized
void Window::_positionButtons(void)
{
	int row_space = 30;
	this->_btns["restart"]->move(0, row_space * 0);
	this->_btns["counter clockwise"]->move(0, row_space * 1);
	this->_btns["clockwise"]->move(145, row_space * 1);
	this->_btns["left"]->move(0, row_space * 2);
	this->_btns["right"]->move(60, row_space * 2);
	this->_btns["down"]->move(0, row_space * 3);
	this->_btns["drop"]->move(0, row_space * 4);
	this->_btns["level down"]->move(0, row_space * 5);
	this->_btns["level up"]->move(95, row_space * 5);
	this->_btns["hint"]->move(0, row_space * 6);
}

void Window::_onButtonPress(std::string command)
{
	// queue button pressed for View to relay to controller
	this->_btnPressed.push_back(command);
}

std::vector<std::string> Window::getButtonInput(void)
{
	std::vector<std::string> buttonInput = this->_btnPressed;
	this->_btnPressed.clear();
	return buttonInput;
}

std::vector<int> Window::getKeyboardInput(void)
{
	std::vector<int> keyboardInput = this->_keyPressed;
	this->_keyPressed.clear();
	return keyboardInput;
}

void Window::render(void)
{
	// trigger paintEvent by updating widget
	QWidget::update();
}

void Window::paintEvent(QPaintEvent* event)
{
	if (event != nullptr) {
		QPainter painter(this);
		this->_drawBoard(painter);
	}
}

void Window::_drawBoard(QPainter& painter)
{
	const Board& board = this->_game->getBoard();
	float cell_size = board.getCellSize();
	for (auto i = board.begin(); i != board.end(); ++i) {
		Cell c = *i;
		float x = c.get_x() * cell_size;
		float y = c.get_y() * cell_size;

		QRectF target = QRectF(x, y, cell_size, cell_size);
		Sprite2D sprite(c.getSprite());
		QPixmap pm = sprite.getData();
		painter.drawPixmap(target, pm, pm.rect());
	}
}

// handle Qt events
bool Window::event(QEvent* event)
{
	switch (event->type()) {
		case QEvent::Close:
			this->_open = false;
			return true;
		case QEvent::Resize:
			this->_width = this->width();
			this->_height = this->height();
			return true;
		default:
			// do not intercept these events
			return QMainWindow::event(event);
	}
}

void Window::keyPressEvent(QKeyEvent* event)
{
	this->_keyPressed.push_back(event->key());
}

void Window::open(void)
{
	this->setVisible(true);
	this->_open = true;
}

void Window::setTitle(const std::string& title)
{
	this->_title = title;
	this->setWindowTitle(title.c_str());
}

void Window::setSize(int width, int height, bool fixed)
{
	this->_width = width;
	this->_height = height;
	if (fixed)
		this->setFixedSize(width, height);
	else
		this->setSize(width, height);
}

bool Window::isOpen(void) const
{
	return _open;
}
