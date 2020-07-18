#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include "View.h"

class GraphicsView : public View
{
public:
	GraphicsView(Game* game);
	std::future<void> start() override;
	void update(void) const override;

private:

};

#endif // GRAPHICSVIEW_H
