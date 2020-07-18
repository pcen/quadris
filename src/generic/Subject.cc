#include "Subject.h"

#include <cassert>

typedef std::lock_guard<std::mutex> thread_lock;

// mutex locks upon subscribe since observers may be
// subscribing from different threads
void Subject::subscribe(Observer* observer)
{
	assert(observer != nullptr);
	thread_lock lk(_lock);
	_observers.emplace(observer);
}

// mutex locks upon unsubscribe since observers may be
// unsubscribing from different threads
void Subject::unsubscribe(Observer* observer)
{
	assert(observer != nullptr);
	thread_lock lk(_lock);
	_observers.erase(observer);
}

// only the thread owning Subject should notify observers, however
// lock mutex to prevent calling notify when an Observer is trying to
// subscribe or unsubscribe
void Subject::_notify(void)
{
	thread_lock lk(_lock);
	for (auto& observer: _observers)
		observer->notify();
}
