#ifndef WINDOW_H
#define WINDOW_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <string>

class X11Window
{
public:
	X11Window(std::string title, int width=640, int height=480);
	~X11Window();

	void start(void);

	void close(void);

	void set_size(int width, int height);
	void set_title(const std::string& title);
	void set_background(unsigned long colour);
	void bring_to_front(void);

	bool is_open(void) const;

private:
	void _handle_events(void);
	void _register_callbacks(void);
	void _cleanup_resources(void);
	XEvent _wm_delete_window_event(void) const;

	Display* _display; // the X server
	int _screen;       // the screen
	Window _window;    // the window
	GC _context;       // graphics context

	XEvent _event;     // current polled event

	int _width, _height;
	std::string _title;
	bool _open;

	unsigned long _black, _white;
};

#endif // WINDOW_H
