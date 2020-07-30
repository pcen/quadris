#include "ViewManager.h"

ViewManager::ViewManager()
{

}

void ViewManager::push(view_ptr view)
{
	if (view != nullptr)
		this->_views.emplace(view);
}

void ViewManager::pop(view_ptr view)
{
	if (view != nullptr)
		this->_views.erase(view);
}

void ViewManager::pollInput(void)
{
	for (auto& view: this->_views) {
		// only poll for events in open views
		if (view != nullptr && view->isOpen())
			view->pollInput();
	}
}
