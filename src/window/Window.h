#ifndef WINDOW_H
#define WINDOW_H

#include <memory>
#include <string>

#include <QApplication>
#include <QLabel>
#include <QWidget>

class Window
{
public:
	Window(std::string title, int argc, char* argv[], int width=640, int height=480);
	~Window();

	void close(void);

	void poll_input(void);
	void set_size(int width, int height);
	void set_title(const std::string& title);
	void set_background(unsigned long colour);

	bool is_open(void) const;

private:
	QApplication _app;
	QLabel _label;

	int _width, _height;
	std::string _title;
	bool _open;

};

#endif // WINDOW_H
