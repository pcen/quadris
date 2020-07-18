#include "Subject.h"

#include <cassert>

void Subject::subscribe(Observer* observer)
{
	assert(observer != nullptr);
	_observers.emplace(observer);
}

void Subject::unsubscribe(Observer* observer)
{
	assert(observer != nullptr);
	_observers.erase(observer);
}

void Subject::_notify(void)
{
	for (auto& observer: _observers)
		observer->notify();
}
