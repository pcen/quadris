#include "Window.h"

#include <stdexcept>
#include <iostream>

#include <QThread>

// class Producer : public QThread
// {
// public:
// 	Producer(QObject *parent = NULL) : QThread(parent)
// 	{

// 	}

// 	void run() override
// 	{
// 	while (true) {
// 		std::cerr << "qt thread run\n";
// 	}

// 	}

// };


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
	if (is_open())
		this->_cleanup_resources();
}

void Window::start(void)
{
	// Producer prod;
	// prod.start();
	// prod.wait();
	std::cerr << "done\n";
}

void Window::close(void)
{
	if (is_open()) {

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

void Window::bring_to_front(void)
{

}

void Window::_handle_events(void)
{

}

void Window::_register_callbacks(void)
{

}

void Window::_cleanup_resources(void)
{
	_open = false;
}
