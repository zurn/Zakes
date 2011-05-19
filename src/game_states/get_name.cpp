
#include "get_name.h"

get_name::get_name()
{
}

get_name::get_name(game * g)
{
	fsm = g;

	name = "_";
	options = new keyboard;	
	title = gfx::loadFont("./data/fonts/mono.ttf", 44);
	caption = gfx::loadFont("./data/fonts/mono.ttf", 24);
	select = audio::loadSfx("./data/sfx/select.wav");
	move = audio::loadSfx("./data/sfx/omove.wav");
}

get_name::~get_name()
{
	delete options;
}

void get_name::draw()
{
	gfx::blendMode();
	gfx::color(0,0,0);

	int xpos = 320 - (title->width(name.c_str())/2);
	title->print(name.c_str(), xpos, 93);

	int x,y;
	x = 320 - (caption->width("You got a new high score!")/2);
	y = 20;

	caption->print("You got a new high score!", x, y);
	caption->print("Please enter your name.", x, y + caption->height());

	options->draw();
}

void get_name::enter()
{
	name = "_";
	options->setPosition(0, 0);
}

void get_name::exit()
{
}

void get_name::update()
{

	if (input::pressed(KEY_P1_ACCEPT)) {
		switch (options->getCursor()) {
//			case KB_CANCEL: 
////				printf("keyboard canceled %s\n", rogue->name.c_str());
//				fsm->change(GS_MAIN_MENU);
//			break;

			case KB_BACK:
				if (name.size() < 2)
					return;

				name.resize(name.size() - 2);
				name += "_";
//				printf("backspace\n");
			break;

			case KB_DONE:
				if (name.size()==1) {
					name.clear();
				}
				else {
					name.resize(name.size() - 1);
				}
				fsm->p1->name = name.c_str();
//				printf("saved name: %s\n", rogue->name.c_str());
				fsm->change(GS_DISP_SCORE);
				fsm->high_score->add_score(fsm->custom->speed, fsm->p1);
			break;

			default: 
//				printf("Pressed: %c\n", options->getCursor());
				if (name.size() > NAME_LENGTH)
					return;
				name[name.size()-1] = options->getCursor();
				name += "_";
			break;
		}
		select->play(0,1);
		return;
	}

	options->update();
}

