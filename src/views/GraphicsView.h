#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include "View.h"
#include "../window/X11Window.h"

#include <string>
#include <memory>

class GraphicsView : public View
{
public:
	GraphicsView(const std::string& name, Game* game);
	std::future<void> start() override;
	void update(void) const override;

	std::unique_ptr<X11Window> _window;
private:

};

#endif // GRAPHICSVIEW_H
