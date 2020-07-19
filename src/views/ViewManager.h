#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include <set>
#include <memory>

#include "View.h"

class ViewManager
{
public:
	ViewManager();

	void push(View* view);
	void pop(View* view);

	void poll_input(void);

private:
	std::set<View*> _views;

};

#endif // VIEWMANAGER_H
