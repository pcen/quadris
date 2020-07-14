#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <gtkmm.h>
#include <memory>

class Window
{
public:
	Window(std::string title, int width, int height, int* argc, char*** argv);

	void launch(void);
	void set_size(int width, int height);

private:
	GtkWidget* _window;
	std::string _title;
};

#endif // WINDOW_H
