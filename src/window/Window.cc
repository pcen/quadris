#include "Window.h"

#include <iostream>

Window::Window(std::string title, int width, int height, Gtk::Main* main)
	: _title{ title }, _gtk_main{ main }
{

}

void Window::set_size(int width, int height)
{

}

void Window::launch(void)
{
	this->_gtk_main->run(this->_window);
}
