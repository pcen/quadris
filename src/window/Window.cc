#include "Window.h"

#include <iostream>

// Gtk::Application must be initialized before Gtk::Window since initializing
// Gtk::Application initializes GTK+
Window::Window(std::string title, int width, int height, int argc, char** argv)
	: _app{ Gtk::Application::create() }, _window{}
{
	this->set_title(title);
	this->set_size(width, height);
}

void Window::launch(void)
{
	this->_app->run(this->_window);
}

void Window::set_size(int width, int height)
{
	this->_window.resize(width, height);
	this->_width = width;
	this->_height = height;
}

void Window::set_title(const std::string& title)
{
	this->_window.set_title(title);
	this->_title = title;
}
