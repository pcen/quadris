#ifndef WINDOW_H
#define WINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/application.h>

class Window
{
public:
	Window(std::string title, int width, int height, int argc, char** argv);

	void launch(void);
	void set_size(int width, int height);
	void set_title(const std::string& title);

private:
	int _width, _height;
	std::string _title;
	Glib::RefPtr<Gtk::Application> _app;
	Gtk::Window _window;
};

#endif // WINDOW_H
