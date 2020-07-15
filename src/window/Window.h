#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <gtkmm.h>
#include <memory>

class Window
{
public:
	Window(std::string title, int width, int height, Gtk::Main* main);

	void launch(void);
	void set_size(int width, int height);

private:
	std::string _title;
	Gtk::Window _window;
	Gtk::Main* _gtk_main;
};

#endif // WINDOW_H
