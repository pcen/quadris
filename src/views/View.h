#ifndef VIEW_H
#define VIEW_H

#include "../game/Game.h"

#include <string>

class View: public Observer
{
public:
	View(Game* _game);
	virtual ~View();
	virtual void start(void) = 0;
	void notify(void) const override;

	std::string get_thread_id(void) const;

protected:
	Game* _game;
};

#endif // VIEW_H
