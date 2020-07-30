#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include "View.h"
#include "../window/Window.h"

#include <string>
#include <QApplication>

class GraphicsView : public View
{
public:
	GraphicsView(const std::string& name, Game* game, Controller* controller);
	void pollInput(void) override;

	void notify(void) const override;

	bool isOpen(void) const override;

private:
	void _shutdown(void);

	int _qtArgCount;
	char** _qtArgs;

	bool _open;
	std::string _name;
	QApplication _app;
	Window _window;
};

#endif // GRAPHICSVIEW_H
