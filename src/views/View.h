#ifndef VIEW_H
#define VIEW_H

#include "../game/Game.h"
#include "../controller/CommandInterpreter.h"

#include <string>

class View: public Observer
{
public:
	View(Game* _game, CommandInterpreter* interpreter);
	virtual ~View();

	virtual void poll_input(void) = 0;
	virtual bool isOpen(void) const = 0;

protected:
	Game* _game;
	CommandInterpreter* _interpreter;
	bool _subscribed;
};

#endif // VIEW_H
