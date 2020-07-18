#ifndef OBSERVER_H
#define OBSERVER_H

class Observer
{
public:
	virtual ~Observer() {}
	void update(void);
};

#endif // OBSERVER_H
