#include "Window.h"

#include <stdexcept>
#include <iostream>

Window::Window(std::string title, int argc, char* argv[], int width, int height)
	: _app(argc, argv),
	 _label("<center>Quadris</center>"),
	_width{ width }, _height{ height }, _open{ false }
{
	_label.setWindowTitle("My First Qt Program");
	_label.resize(_width, _height);
	_label.show();
}

Window::~Window()
{

}

void Window::poll_input(void)
{
	_app.processEvents();
}

void Window::close(void)
{
	if (is_open()) {

		_open = false;
	}
}

bool Window::is_open(void) const
{
	return _open;
}

void Window::set_size(int width, int height)
{
	_width = width;
	_height = height;

}

void Window::set_title(const std::string& title)
{

}

void Window::set_background(unsigned long colour)
{

}
