
#ifndef __GAMEPLAY_H__
#define __GAMEPLAY_H__

#include "state.h"
//#include "gfx.h"
//#include "world.h"
//#include "machine.h"
#include "game.h"
#include "input.h"

class game;

class gameplay: public state
{
	public:
		gameplay(game * fsm);
		gameplay();
		~gameplay();
	
		void update();
		void draw();
		void enter();
		void exit();

		game * fsm;
	private:

};



#endif /* __GAMEPLAY_H__ */
