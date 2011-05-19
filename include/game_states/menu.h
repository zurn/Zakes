
#ifndef __MENU_H__
#define __MENU_H__

#include "state.h"
//#include "gfx.h"
//#include "world.h"
//#include "machine.h"
#include "game.h"
#include "input.h"
#include "audio.h"
#include "gfx.h"

class game;

#define MM_SINGLE 0
//#define MM_TWO 1
#define MM_SPEED 1
#define MM_HIGH 2
#define MM_OPTIONS 3
#define MM_QUIT 4

#define SPEED_STR "Game speed"

enum speed
{
	SLOW = 0,
	MEDIUM,
	FAST
};


class menu: public state
{
	public:
		menu(game * fsm);
		virtual ~menu();
	
		void update();
		void draw();
		void enter();
		void exit();

		game * fsm;
		void setHot(int n);
	private:
		menu();
		font * title;
		font * opt;
		font * opt2;
		sound * select;
		sound * move;
		image * bg;

		std::vector<std::string> options;
		int hot;
		speed game_speed;

};



#endif /* __MENU_H__ */
