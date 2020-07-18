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
	virtual void start(void) = 0;
	void notify(void) const override;

	std::string get_thread_id(void) const;

protected:
	Game* _game;
	CommandInterpreter* _interpreter;
};

#endif // VIEW_H
