
#include "pause_menu.h"

pause_menu::pause_menu() { }

pause_menu::pause_menu(game * g)
{
	fsm = g;

	opt = gfx::load_font("./data/fonts/mono.ttf", 20);
	opt2 = gfx::load_font("./data/fonts/mono.ttf", 16);
	title = gfx::load_font("./data/fonts/mono.ttf", 44);
	select = audio::load_sfx("./data/sfx/select.wav");
	move = audio::load_sfx("./data/sfx/omove.wav");


	options.push_back("Resume Game");
	options.push_back("Options");
	options.push_back("Quit");
	setHot(0);
}

pause_menu::~pause_menu()
{
}

void pause_menu::draw()
{
	gfx::blendMode();
	gfx::color(0,0,0);
	std::string name("Paused");
	int xpos = 320 - (title->width(name.c_str())/2);
	title->print(name.c_str(), xpos, 73);

	int x = 16*14, y = 16*9;
	std::string Hot = "(*) ";
	std::string Cold = "( ) ";
	std::string ts;

	for (unsigned int i=0; i<options.size(); i++) {

		if (hot == int(i)) {
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
void pause_menu::enter()
{
	setHot(0);
}

void pause_menu::exit()
{
}

void pause_menu::setHot(int n)
{
	if (n < 0) {
		hot = PA_QUIT;
		return;
	}
	if (n > PA_QUIT) {
		hot = 0;
		return;
	}
	hot = n;
}

void pause_menu::update()
{
	if (input::pressed(KEY_P1_ACCEPT)) {
		switch(hot) {
			case PA_RESUME:
				select->play(0,1);
				fsm->change(GS_GAMEPLAY);
//				fsm->revert();
			break;
			case PA_OPTIONS:
				select->play(0,1);
				fsm->change(GS_OPTIONS_MENU);
				fsm->last = fsm->states[GS_PAUSE];
			break;

			case PA_QUIT:
				select->play(0,1);
				fsm->change(GS_MAIN_MENU);
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
//	if (input::pressed(KEY_P1_ACCEPT)) {
//		fsm->revert();
//		return;
//	}
}

