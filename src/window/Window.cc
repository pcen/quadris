#include "Window.h"

#include <iostream>

Window::Window(std::string title, int width, int height, int* argc, char*** argv)
	: _title{ title }
{
	gtk_init(argc, argv);
	this->_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	this->set_size(width, height);
	// register gtk callback functions for application window
	g_signal_connect(this->_window, "delete-event", G_CALLBACK(gtk_main_quit), nullptr);
}

void Window::set_size(int width, int height)
{
	gtk_widget_set_size_request(this->_window, width, height);
}

void Window::launch(void)
{
	gtk_widget_show(this->_window);
	gtk_main();
}
