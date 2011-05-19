
#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "state.h"
//#include "gfx.h"
//#include "world.h"
//#include "machine.h"
#include "game.h"
#include "input.h"
#include "audio.h"

class game;

class game_over: public state
{
	public:
		game_over(game * fsm);
		game_over();
		~game_over();
	
		void update();
		void draw();
		void enter();
		void exit();

		game * fsm;
	private:

};



#endif /* __GAME_OVER_H__ */
