
#ifndef __PAUSE_MENU_H__
#define __PAUSE_MENU_H__

#include "state.h"
#include "game.h"
#include "input.h"
#include "audio.h"
#include "gfx.h"
#include <vector>

#define PA_RESUME 0
#define PA_OPTIONS 1
#define PA_QUIT 2

class game;

class pause_menu: public state
{
	public:
		pause_menu(game * g);
		virtual ~pause_menu();

		void update();
		void draw();
		void enter();
		void exit();

		game * fsm;
		void setHot(int n);
	private:
		pause_menu();
		font * title;
		font * opt;
		font * opt2;
		sound * select;
		sound * move;

		std::vector<std::string> options;
		int hot;


};
#endif /* __PAUSE_MENU_H__ */
