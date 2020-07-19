#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include "View.h"
// #include "../window/X11Window.h"

#include <string>
#include <memory>
#include <future>

class GraphicsView : public View
{
public:
	GraphicsView(const std::string& name, Game* game, CommandInterpreter* interpreter);
	void start() override;
	void notify(void) const override;

	static std::future<void> create(const std::string&, Game*, CommandInterpreter*);

private:
	// std::unique_ptr<X11Window> _window;

};

#endif // GRAPHICSVIEW_H
