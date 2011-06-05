
#include "menu.h"

menu::menu() { }
menu::~menu() { }

menu::menu(game * fsm)
{
	menu::fsm = fsm;

	opt = gfx::load_font("./data/fonts/mono.ttf", 20);
	opt2 = gfx::load_font("./data/fonts/mono.ttf", 16);
	title = gfx::load_font("./data/fonts/mono.ttf", 44);
	select = audio::load_sfx("./data/sfx/select.wav");
	move = audio::load_sfx("./data/sfx/omove.wav");


	options.push_back("Start Game");
//	options.push_back("2 Player");
	options.push_back(SPEED_STR);
	options.push_back("High Scores");
	options.push_back("Options");
	options.push_back("Quit");
	setHot(0);
	switch (fsm->custom->speed) {
		case 0:
			game_speed = SLOW;
			fsm->p1->advance_delay = SPEED_SLOW;
		break;
		case 1:
			game_speed = MEDIUM;
			fsm->p1->advance_delay = SPEED_MEDIUM;
		break;
		case 2:
			game_speed = FAST;
			fsm->p1->advance_delay = SPEED_FAST;
		break;
	}
}

void menu::draw()
{

	gfx::blendMode();
	gfx::color(0,0,0);
	std::string name("Snake Clone");
	int xpos = 320 - (title->width(name.c_str())/2);
	title->print(name.c_str(), xpos, 73);

	int x = 16*14, y = 16*9;
	std::string Hot = "(*) ";
	std::string Cold = "( ) ";
	std::string ts;

	for (unsigned int i=0; i<options.size(); i++) {

		if (i == MM_SPEED+1 && hot == MM_SPEED) {
			ts = "";
			switch (game_speed) {
				case SLOW:
					ts += Hot;
					ts += "Slow ";
					ts += Cold;
					ts += "Medium ";
					ts += Cold;
					ts += "Fast";
				break;
				case MEDIUM:
					ts += Cold;
					ts += "Slow ";
					ts += Hot;
					ts += "Medium ";
					ts += Cold;
					ts += "Fast";
				break;
				case FAST:
					ts += Cold;
					ts += "Slow ";
					ts += Cold;
					ts += "Medium ";
					ts += Hot;
					ts += "Fast";
				break;

			}
			opt2->print(ts.c_str(), x+ 40, y + (opt->height() * i));


			y += opt->height();
		}
		else {
			options[MM_SPEED] = SPEED_STR;
			switch (game_speed) {
				case SLOW: options[MM_SPEED] += " - Slow"; break;
				case MEDIUM: options[MM_SPEED] += " - Medium"; break;
				case FAST: options[MM_SPEED] += " - Fast"; break;
			}
		}
		if (hot == int(i)) {
//			if (hot == MM_TWO)
//				gfx::color(.5,.5,.5);
//			else
				gfx::color(0,0,0);
			ts = Hot + options[i];
		}
		else {
			gfx::color(.5, .5, .5);
			ts = Cold + options[i];
		}
		opt->print(ts.c_str(), x, y + (opt->height() * i));
	}

}

void menu::update()
{

	if (input::pressed(KEY_P1_ACCEPT)) {
		switch(hot) {
			case MM_SINGLE:
				select->play(0,1);
				fsm->loadLevel();
				fsm->change(GS_GAMEPLAY);
			break;
			case MM_OPTIONS:
				select->play(0,1);
				fsm->change(GS_OPTIONS_MENU);
			break;

			case MM_HIGH:
				select->play(0,1);
				fsm->change(GS_DISP_SCORE);
			break;

			case MM_QUIT:
				select->play(0,1);
				input::quit = 1;
			break;

			default: break;
		}
		return;
	}

	if (input::pressed(KEY_P1_UP)) {
		setHot(hot-1);
		move->play(0,1);
		return;
	}

	if (input::pressed(KEY_P1_DOWN)) {
		setHot(hot+1);
		move->play(0,1);
		return;
	}


	if (input::pressed(KEY_P1_LEFT) && hot == MM_SPEED) {
		select->play(0,1);
		switch (game_speed) {
			case SLOW:
				fsm->p1->advance_delay = SPEED_SLOW;
				fsm->custom->speed = 0;
			break;
			case MEDIUM:
				game_speed = SLOW;
				fsm->p1->advance_delay = SPEED_SLOW;
				fsm->custom->speed = 0;
			break;
			case FAST:
				game_speed = MEDIUM;
				fsm->p1->advance_delay = SPEED_MEDIUM;
				fsm->custom->speed = 1;
			break;

		}
		return;
	}

	if (input::pressed(KEY_P1_RIGHT) && hot == MM_SPEED) {
		select->play(0,1);
		switch (game_speed) {
			case SLOW:
				game_speed = MEDIUM;
				fsm->p1->advance_delay = SPEED_MEDIUM;
				fsm->custom->speed = 1;
			break;
			case MEDIUM:
				game_speed = FAST;
				fsm->p1->advance_delay = SPEED_FAST;
				fsm->custom->speed = 2;
			break;
			case FAST:
				fsm->p1->advance_delay = SPEED_FAST;
				fsm->custom->speed = 2;
			break;

		}
		return;
	}
}

void menu::enter()
{
	setHot(0);
//	printf("entering mmenu state\n");
	switch (fsm->custom->speed) {
		case 0: game_speed = SLOW; break;
		case 1: game_speed = MEDIUM; break;
		case 2: game_speed = FAST; break;
	}
}

void menu::exit()
{
}

void menu::setHot(int n)
{
	if (n < 0) {
		hot = MM_QUIT;
		return;
	}
	if (n > MM_QUIT) {
		hot = 0;
		return;
	}
	hot = n;
}

