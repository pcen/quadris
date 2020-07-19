#include "ViewManager.h"

ViewManager::ViewManager()
{

}

void ViewManager::push(View* view)
{
	if (view != nullptr)
		this->_views.emplace(view);
}

void ViewManager::pop(View* view)
{
	if (view != nullptr)
		this->_views.erase(view);
}

void ViewManager::poll_input(void)
{
	for (auto& view: this->_views) {
		// only poll for events in open views
		if (view->isOpen())
			view->poll_input();
	}
}
