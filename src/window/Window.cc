#include "Window.h"

#include <stdexcept>
#include <iostream>
#include <QEvent>
#include <QPainter>

Window::Window(const std::string& title, QWidget* parent, int width, int height)
	: QMainWindow(parent), _open{ false }
{
	this->setTitle(title);
	this->setSize(width, height);
	this->_card.loadAsset("./assets/card.png");
}

Window::~Window() {}

void Window::render(void)
{
	// trigger paintEvent by updating widget
	// QWidget::update();
}

void Window::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	for (int i = 0; i < 10; i++) {
		int x = (this->_width / 15) * i;
		int y = (this->_height / 15) * i;
		painter.drawPixmap(x, y, this->_card.getData());
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

void Window::setSize(int width, int height)
{
	this->_width = width;
	this->_height = height;
	this->resize(width, height);
}

bool Window::isOpen(void) const
{
	return _open;
}
