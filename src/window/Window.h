#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <memory>

#include <gtkmm/window.h>
#include <gtkmm-2.4/gtkmm/main.h>

namespace Gtk{
class Window;
class Main;
}

class Window
{
public:
	Window(std::string title, int width, int height, Gtk::Main* main);

	void launch(void);
	void set_size(int width, int height);
	void set_title(const std::string& title);
	void fullscreen(bool fullscreen);

private:
	int _width, _height;
	std::string _title;
	Gtk::Window _window;
	Gtk::Main* _gtk_main;
};

#endif // WINDOW_H
