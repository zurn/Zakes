
#include "game.h"

game::game(settings * options)
{
	level = new world;
	p1 = new player(level);
	p2 = NULL;

	custom = options;
	create_states();


	loadLevel();
	high_score = new scores(HIGH_SCORE_FILE);
	high_score->load(HIGH_SCORE_FILE);
}

game::game() { }

game::~game()
{
	high_score->save(HIGH_SCORE_FILE);
	delete high_score;
}

void game::cleanup()
{
	for (unsigned int i=0; i<states.size(); i++) {
		if (states[i] != NULL)
			delete states[i];
	}
delete level;
	delete p1;
}

void game::create_states()
{
//	printf("create game states\n");

	states.resize(GS_NUM_STATES, NULL);

	menu * Menu = new menu(this);
	states[GS_MAIN_MENU] = Menu;

	gameplay * Gameplay = new gameplay(this);
	states[GS_GAMEPLAY] = Gameplay;

	game_over * over = new game_over(this);
	states[GS_GAME_OVER] = over;

	options * opts = new options(this);
	states[GS_OPTIONS_MENU] = opts;

	config_p1 * cp1 = new config_p1(this);
	states[GS_CONFIG_P1] = cp1;

	disp_score * ds = new disp_score(this);
	states[GS_DISP_SCORE] = ds;

	get_name * gn = new get_name(this);
	states[GS_GET_NAME] = gn;

	pause_menu * pa = new pause_menu(this);
	states[GS_PAUSE] = pa;

	current = Menu;
}

void game::loadLevel()
{
	while (!level->init("./data/levels/world01.sl"));
//	level->init(filename);
	p1->reset();

	addCherry(true);
}

void game::addCherry(bool player1)
{
	if (p1 == NULL || level == NULL) return;

	int x,y;

	do {
		x = ran1_int(0, level->width);
		y = ran1_int(0, level->height);
	} while (p1->collide(x,y) || (*level->walls)(x,y));

	(*level->cherries)(x,y) = 1;

	if (player1) {
		if ((p1->cherry_count) % 10 == 0) {

			do {
				x = ran1_int(0, level->width);
				y = ran1_int(0, level->height);
			} while (p1->collide(x,y) || (*level->walls)(x,y));

			(*level->cherries)(x,y) = 1;
		}
	}


}

