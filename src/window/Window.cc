#include "Window.h"

#include <iostream>

Window::Window(std::string title, int width, int height, Gtk::Main* main)
	: _gtk_main{ main }
{
	this->set_title(title);
	this->set_size(width, height);
}

void Window::launch(void)
{
	this->_gtk_main->run(this->_window);
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

