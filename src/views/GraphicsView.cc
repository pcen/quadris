#include "GraphicsView.h"

#include <iostream>

GraphicsView::GraphicsView(Game* game)
	: View{ game }
{

}

void GraphicsView::update(void) const
{
	std::cerr << "GraphicsView::update\n";
}

std::future<void> GraphicsView::start(void)
{
	return std::async(std::launch::async, [](){
		return;
	});
}
