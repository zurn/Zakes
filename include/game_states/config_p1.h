
#ifndef __CONFIG_P1_H__
#define __CONFIG_P1_H__

#include "state.h"
#include "game.h"

#define CP_CONFIRM 0
#define CP_UP 1
#define CP_DOWN 2
#define CP_LEFT 3
#define CP_RIGHT 4
#define CP_DEFAULT 5
#define CP_BACK 6

class config_p1: public state
{
	public:
		config_p1(game * g);
		virtual ~config_p1();

		void update();
		void draw();
		void enter();
		void exit();

		game * fsm;
		void setHot(int n);
		bool checkKey(int keydef);
	private:
		config_p1();
		font * title;
		font * opt;
		sound * select;
		sound * move;
		sound * bad;

		std::vector<std::string> opts;
		std::vector<std::string> names;
		int hot;
		bool capture;

		state * store;

	private:

};

#endif /* __CONFIG_P1_H__ */
