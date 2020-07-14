#include <iostream>

#include "window/Window.h"

int main(int argc, char* argv[])
{
	Window Window("Quadris", 640, 480, &argc, &argv);
	Window.launch();
	return 0;
}
