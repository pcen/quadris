#include "X11Window.h"

#include <stdexcept>
#include <iostream>

// https://en.wikibooks.org/wiki/X_Window_Programming/Xlib
// http://mech.math.msu.su/~nap/2/GWindow/xintro.html

X11Window::X11Window(std::string title, int width, int height)
	: _width{ width }, _height{ height }, _open{ false }
{
	// nullptr parameter defaults to environment variable DISPLAY
	_display = XOpenDisplay(nullptr);
	if (_display == nullptr)
		std::cerr << "XOpenDisplay returned nullptr\n";

	_screen = DefaultScreen(_display);

	// permanent entries of the default colour map
	_black = BlackPixel(_display, _screen);
	_white = WhitePixel(_display, _screen);

	_window = XCreateSimpleWindow(
		_display,
		DefaultRootWindow(_display),
		25,      // window position
		25,
		_width,
		_height,
		10,      // border width
		_white,  // foreground
		_black   // background
	);

	_context = XCreateGC(_display, _window, 0, 0);

	// select input types to respond to
	XSelectInput(_display, _window, ButtonPressMask | KeyPressMask);

	this->bring_to_front();
	this->set_title(title);
	this->set_size(width, height);
	this->_register_callbacks();
	_open = true;
}

X11Window::~X11Window()
{
	// if the X11 window hasn not been closed do cleanup
	if (is_open())
		_cleanup_resources();
}

void X11Window::start(void)
{
	while (is_open()) {
		_handle_events();
	}
}

bool X11Window::is_open(void) const
{
	return _open;
}

void X11Window::set_size(int width, int height)
{
	_width = width;
	_height = height;
}

void X11Window::set_title(const std::string& title)
{
	_title = title;
	XSetStandardProperties(
		_display,
		_window,
		_title.c_str(),
		_title.c_str(),
		0,
		nullptr,
		0,
		nullptr
	);
	XFlush(_display);
}

void X11Window::set_background(unsigned long colour)
{
	XSetBackground(_display, _context, colour);
	XFlush(_display);
}

void X11Window::bring_to_front(void)
{
	XMapRaised(_display, _window);
	XFlush(_display);
}

void X11Window::_handle_events(void)
{
	XNextEvent(_display, &_event);
	switch (_event.type) {
		case ClientMessage:
			// TODO: check if the client message is window closed
			_cleanup_resources();
			break;
		default:
			break;
	}
}

void X11Window::_register_callbacks(void)
{
	// handle window closing in event loop to manage
	// cleanup of X11 resources
	Atom WM_DELETE_WINDOW = XInternAtom(_display, "WM_DELETE_WINDOW", 1);
	XSetWMProtocols(_display, _window, &WM_DELETE_WINDOW, 1);
	XFlush(_display);
}

void X11Window::_cleanup_resources(void)
{
	XFlush(_display);
	XFreeGC(_display, _context);
	XDestroyWindow(_display, _window);
	XCloseDisplay(_display);
	// _open = false prevents double deletion of X11 resources
	// in the class destructor
	_open = false;
}
