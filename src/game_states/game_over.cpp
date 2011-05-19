
#include "game_over.h"

game_over::game_over()
{
}

game_over::~game_over()
{
}
game_over::game_over(game * fsm)
{
	game_over::fsm = fsm;
}

void game_over::draw()
{
	fsm->level->draw();
	fsm->p1->draw();


	gfx::blendMode();
	gfx::color(1,0,0);
	const char * c = "Game over";
	font * f = gfx::loadFont("./data/fonts/mono.ttf", 66);

	f->print(c, 320-f->width(c)/2, 240 - f->height());
}

void game_over::update()
{
//	if (input::anykey) {
	if (input::pressed(KEY_P1_ACCEPT) ) {
//		if (fsm->high_score->add_score(fsm->custom->speed, fsm->p1) > 0) {
		if (fsm->high_score->is_new_highscore(fsm->custom->speed, fsm->p1) > 0) {
			fsm->change(GS_GET_NAME);
//			printf("new place: %i\n", temp);
		}
		else {
			fsm->change(GS_MAIN_MENU);
		}
	}
}

void game_over::enter()
{
}

void game_over::exit()
{
	audio::stopSfx();
}

