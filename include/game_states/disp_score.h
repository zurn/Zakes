
#ifndef __DISP_SCORE_H__
#define __DISP_SCORE_H__

#include "game.h"
#include "state.h"

#define DS_SLOW 0
#define DS_MEDIUM 1
#define DS_FAST 2

class disp_score: public state
{
	public:
		disp_score(game * fsm);
		virtual ~disp_score();

		void update();
		void draw();
		void enter();
		void exit();

		void draw(std::vector<entry> & entries, int x, int y);
		game * fsm;

		font * opt;
		font * opt2;
		font * title;
		sound * select;
		sound * move;
	private:
		int selected;

};
#endif /* __DISP_SCORE_H__ */
