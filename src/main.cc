#include <iostream>

#include "window/Window.h"

int main(int argc, char* argv[])
{
	Gtk::Main gtk_main(argc, argv);
	Window window("Quadris", 640, 480, &gtk_main);
	window.launch();
	return 0;
}
