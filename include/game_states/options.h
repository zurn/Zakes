
#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include "state.h"
#include "game.h"

#define OM_SFX 0
#define OM_MUS 1
#define OM_SKIP 2
#define OM_CONFIG 3
#define OM_DEFAULT 4
#define OM_BACK 5

class options: public state
{
	public:
		options(game * fsm);
		virtual ~options();
	
		void update();
		void draw();
		void enter();
		void exit();

		game * fsm;
		void setHot(int n);

	private:

		options();
		font * title;
		font * opt;
		font * opt2;
		sound * select;
		sound * move;

		std::vector<std::string> opts;
		int hot;

		float music_vol;
		float sfx_vol;
};


#endif /* __OPTIONS_H__ */
