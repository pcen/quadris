#ifndef VIEW_H
#define VIEW_H

#include "../game/Game.h"

class View: public Observer
{
public:
	View(Game* _game);
	virtual ~View();
	virtual void start(void) = 0;
	void notify(void) const override;

protected:
	Game* _game;
};

#endif // VIEW_H
