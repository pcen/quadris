#include "Subject.h"

#include <cassert>

typedef std::lock_guard<std::mutex> thread_lock;

void Subject::subscribe(Observer* observer)
{
	assert(observer != nullptr);
	thread_lock lock(_subject_lock);
	_observers.emplace(observer);
}

void Subject::unsubscribe(Observer* observer)
{
	assert(observer != nullptr);
	thread_lock lock(_subject_lock);
	_observers.erase(observer);
}

void Subject::_notify(void)
{
	for (auto& observer: _observers)
		observer->notify();
}
