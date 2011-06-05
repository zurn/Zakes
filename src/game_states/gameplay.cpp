
#include "gameplay.h"

gameplay::gameplay() { }

gameplay::~gameplay()
{
}
gameplay::gameplay(game * fsm)
{
	gameplay::fsm = fsm;
}

void gameplay::draw()
{
	fsm->level->draw();
	fsm->p1->draw();
	gfx::blendMode();
	gfx::color(0,0,0);
//	char buf[256];
//	buf[255] = '\0';
	const char * buf;
	font * text = gfx::load_font("./data/fonts/mono.ttf", 18);

	switch (fsm->custom->speed) {
		case 0: buf = "Game Speed - Slow"; break;
		case 1: buf = "Game Speed - Medium"; break;
		case 2: buf = "Game Speed - Fast"; break;

	}


	text->print(buf, 2 + 200 ,463);
}

void gameplay::update()
{
	if (input::pressed(KEY_P1_ACCEPT)) {
		fsm->change(GS_PAUSE);
		return;
	}
	fsm->p1->update();
	if (fsm->p1->dead) {
//		fsm->p1->print();
		fsm->change(GS_GAME_OVER);
	}
	if (fsm->p1->grew) {
		fsm->p1->cherry_count++;
		fsm->addCherry(true);
		fsm->p1->grew = false;
	}
//	if (input::pressed(KEY_P1_ACCEPT)) {
//		fsm->change(GS_OPTIONS_MENU);
//	}
	//TODO: add pause menu thing
}

void gameplay::enter()
{
}

void gameplay::exit()
{
}

