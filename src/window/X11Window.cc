// #include "X11Window.h"

// #include <stdexcept>
// #include <iostream>

// #define SIZE_OF_LONG 32

// // https://en.wikibooks.org/wiki/X_Window_Programming/Xlib
// // http://mech.math.msu.su/~nap/2/GWindow/xintro.html
// // https://www.student.cs.uwaterloo.ca/~cs349/f15/resources/X/xTutorialPart2.html

// X11Window::X11Window(std::string title, int width, int height)
// 	: _width{ width }, _height{ height }, _open{ false }
// {
// 	// nullptr parameter defaults to environment variable DISPLAY
// 	_display = XOpenDisplay(nullptr);
// 	if (_display == nullptr)
// 		std::cerr << "XOpenDisplay returned nullptr\n";

// 	_screen = DefaultScreen(_display);

// 	// permanent entries of the default colour map
// 	_black = BlackPixel(_display, _screen);
// 	_white = WhitePixel(_display, _screen);

// 	_window = XCreateSimpleWindow(_display, DefaultRootWindow(_display), 25, 25,
// 	                              _width, _height, 10, _white, _black);

// 	_context = XCreateGC(_display, _window, 0, 0);

// 	// select input types to respond to
// 	XSelectInput(_display, _window, ButtonPressMask | KeyPressMask);

// 	this->bring_to_front();
// 	this->set_title(title);
// 	this->_register_callbacks();
// 	_open = true;
// }

// X11Window::~X11Window()
// {
// 	if (is_open())
// 		this->_cleanup_resources();
// }

// void X11Window::start(void)
// {
// 	while (is_open())
// 		this->_handle_events();
// }

// void X11Window::close(void)
// {
// 	if (is_open()) {
// 		XEvent e = this->_wm_delete_window_event();
// 		XSendEvent(_display, _window, 0, 0, &e);
// 		XFlush(_display);
// 	}
// }

// bool X11Window::is_open(void) const
// {
// 	return _open;
// }

// void X11Window::set_size(int width, int height)
// {
// 	_width = width;
// 	_height = height;
// 	XMoveResizeWindow(_display, _window, 0, 0,
// 	                  (unsigned int) width, (unsigned int) height);
// 	XFlush(_display);
// }

// void X11Window::set_title(const std::string& title)
// {
// 	_title = title;
// 	XSetStandardProperties(_display, _window, _title.c_str(),
// 	                       _title.c_str(), 0, nullptr, 0, nullptr);
// 	XFlush(_display);
// }

// void X11Window::set_background(unsigned long colour)
// {
// 	XSetBackground(_display, _context, colour);
// 	XFlush(_display);
// }

// void X11Window::bring_to_front(void)
// {
// 	XMapRaised(_display, _window);
// 	XFlush(_display);
// }

// void X11Window::_handle_events(void)
// {
// 	XNextEvent(_display, &_event);
// 	switch (_event.type) {
// 		case ClientMessage:
// 			this->_cleanup_resources();
// 			this->_open = false;
// 			break;
// 		default:
// 			break;
// 	}
// }

// void X11Window::_register_callbacks(void)
// {
// 	Atom WM_DELETE_WINDOW = XInternAtom(_display, "WM_DELETE_WINDOW", 1);
// 	XSetWMProtocols(_display, _window, &WM_DELETE_WINDOW, 1);
// 	XFlush(_display);
// }

// void X11Window::_cleanup_resources(void)
// {
// 	XFlush(_display);
// 	XFreeGC(_display, _context);
// 	XDestroyWindow(_display, _window);
// 	XCloseDisplay(_display);
// 	// prevents double deletion of X11 resources in the class destructor
// 	// TODO: should probably have a separate _has_resources boolean
// 	_open = false;
// }

// // use to close X11 window with an XEvent
// XEvent X11Window::_wm_delete_window_event(void) const
// {
// 	XEvent e;
// 	e.xclient.type = ClientMessage;
// 	e.xclient.window = _window;
// 	e.xclient.message_type = XInternAtom(_display, "WM_PROTOCOLS", 1);
// 	e.xclient.format = SIZE_OF_LONG;
// 	e.xclient.data.l[0] = XInternAtom(_display, "WM_DELETE_WINDOW", 1);
// 	e.xclient.data.l[1] = 0;
// 	return e;
// }
