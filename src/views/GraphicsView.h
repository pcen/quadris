#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include "View.h"
#include "../window/X11Window.h"

#include <string>
#include <memory>
#include <future>

class GraphicsView : public View
{
public:
	GraphicsView(const std::string& name, Game* game);
	void start() override;
	void notify(void) const override;

	std::unique_ptr<X11Window> _window;

	static std::future<void> create(Game* game);

private:

};

#endif // GRAPHICSVIEW_H
