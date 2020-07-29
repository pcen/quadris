#include "Window.h"

#include <stdexcept>
#include <iostream>
#include <QEvent>
#include <QPainter>

#define BUTTON_COUNT 10

static const char* buttonLabels[BUTTON_COUNT] = {
	"left", "right", "down", "drop", "clockwise", "counter clockwise",
	"level up", "level down", "restart", "hint"
};

Window::Window(const std::string& title, QWidget* parent, int width, int height)
	: QMainWindow(parent), _open{ false }, _buttonPane{ this }
{
	this->setTitle(title);
	this->setSize(width, height);
	this->_board = Board("./assets/_.png");
	this->_initializeButtons();
}

Window::~Window()
{

}

// precondition: _board must be initialized
void Window::_initializeButtons(void)
{
	// set button pane position
	int btnOffset = this->_board.get_cell_size() * 12;
	this->_buttonPane.move({btnOffset, 0});

	// populate the button pane
	for (auto & label : buttonLabels) {
		QButtonPtr button(new QPushButton(label, &this->_buttonPane));
		this->_buttons.insert(label, button);
	}

}

void Window::render(void)
{
	// trigger paintEvent by updating widget
	// QWidget::update();
}

void Window::paintEvent(QPaintEvent* event)
{
	if (event != nullptr) {
		QPainter painter(this);
		this->_draw_board(painter);
	}
}

void Window::_draw_board(QPainter& painter)
{
	float cell_size = this->_board.get_cell_size();
	for (auto i = this->_board.begin(); i != this->_board.end(); ++i) {
		std::shared_ptr<Cell> currCell = *i;
		if (currCell != nullptr) {
			float x = currCell->get_x() * cell_size;
			float y = currCell->get_y() * cell_size;

			QRectF target = QRectF(x, y, cell_size, cell_size);
			QPixmap pm = currCell->getSprite().getData();
			QRectF source = pm.rect();

			painter.drawPixmap(target, pm, source);
		}
	}
}

// TODO: move into separate callbacks
bool Window::event(QEvent* event)
{
	switch (event->type()) {
		case QEvent::Close:
			this->_open = false;
			return true;
		case QEvent::Resize:
			// store window size in API agnostic implementation
			this->_width = this->width();
			this->_height = this->height();
			return true;
		default:
			// do not intercept these events
			return QMainWindow::event(event);
	}
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
