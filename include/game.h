
#ifndef __GAME_H__
#define __GAME_H__

#define HIGH_SCORE_FILE "./data/score.xml"

#include <stdio.h>
#include "machine.h"
#include "settings.h"
#include "world.h"
#include "player.h"
#include "scores.h"


#include "game_states.h"
#include "menu.h"
#include "game_over.h"
#include "gameplay.h"
#include "options.h"
#include "config_p1.h"
#include "disp_score.h"
#include "get_name.h"
#include "pause_menu.h"

class game: public machine
{
	public:
		game(settings * options);
		virtual ~game();

		void cleanup();

		void loadLevel();
		void create_states();
		void addCherry(bool player1);
		//adds a cherry to random open position on map
		//adds a cherry for player 1 if player1==true
		//adds a cherry for player 2 if player1==false

		world * level;
		player * p1;
		player * p2;
		settings * custom;
		scores * high_score;
	private:
		game();
};




#endif /* __GAME_H__ */
