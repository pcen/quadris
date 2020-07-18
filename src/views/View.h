#ifndef VIEW_H
#define VIEW_H

#include <future>
#include <thread>

#include "../game/Game.h"

class View: public Observer
{
public:
	View(Game* _game);
	virtual ~View();
	virtual std::future<void> start(void) = 0;
	void update(void) const override;

protected:
	Game* _game;
};

#endif // VIEW_H
