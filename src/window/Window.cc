#include "Window.h"

#include <stdexcept>
#include <iostream>

#include <QtGui/QtGui>
#include <QMessageBox>

Window::Window(QWidget* parent)
	: QMainWindow(parent)
{
	setWindowTitle("Quadris");
}

void Window::closeEvent(QCloseEvent* event)
{
	if (this->confirmClose())
		event->accept();
	else
		event->ignore();
}

bool Window::confirmClose(void)
{
	int res = QMessageBox::warning(this, windowTitle(), "Quit Game?",
	                               QMessageBox::Yes | QMessageBox::No);
	if(res == QMessageBox::No)
		return false;
	return true;
}

void Window::poll_input(void)
{

}

void Window::close(void)
{

}

bool Window::is_open(void) const
{

}

void Window::set_size(int width, int height)
{

}

void Window::set_title(const std::string& title)
{

}

void Window::set_background(unsigned long colour)
{

}
