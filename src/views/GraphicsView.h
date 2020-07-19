#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include "View.h"
#include "../window/Window.h"

#include <string>
#include <QApplication>

class GraphicsView : public View
{
public:
	GraphicsView(const std::string& name, Game* game, CommandInterpreter* interpreter, int argc, char** argv);
	void poll_input(void) override;

	void notify(void) const override;

	bool isOpen(void) const override;

private:

	void _shutdown(void);

	bool _open;
	std::string _name;
	QApplication _app;
	Window _window;
};

#endif // GRAPHICSVIEW_H
