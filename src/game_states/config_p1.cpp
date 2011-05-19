
#include "config_p1.h"

config_p1::config_p1() { }

config_p1::config_p1(game * g)
{
	fsm = g;
	capture = false;

	opt = gfx::loadFont("./data/fonts/mono.ttf", 20);
	title = gfx::loadFont("./data/fonts/mono.ttf", 44);
	select = audio::loadSfx("./data/sfx/select.wav");
	move = audio::loadSfx("./data/sfx/omove.wav");
	bad = audio::loadSfx("./data/sfx/bad.wav");

	opts.push_back("Confirm");
	opts.push_back("Up");
	opts.push_back("Down");
	opts.push_back("Left");
	opts.push_back("Right");
	opts.push_back("Restore Default Controls");
	opts.push_back("Back");

	names.push_back(input::name(KEY_P1_ACCEPT));
	names.push_back(input::name(KEY_P1_UP));
	names.push_back(input::name(KEY_P1_DOWN));
	names.push_back(input::name(KEY_P1_LEFT));
	names.push_back(input::name(KEY_P1_RIGHT));

	setHot(0);
}

config_p1::~config_p1()
{
}

void config_p1::draw()
{
	gfx::blendMode();
	gfx::color(0,0,0);
	std::string name("Configure Controls");
	int xpos = 320 - (title->width(name.c_str())/2);
	int ypos = 53;
	title->print(name.c_str(), xpos, ypos);
//	opt->print("Player 1", xpos + 10, ypos + title->height());

	int x = 16*6, y = 16*10;
	int x2 = 16 *28;

	opt->print("Action ", x, y-21);
	opt->print("Button", x2, y-21);

	std::string Hot = "(*) ";
	std::string Cold = "( ) ";
	std::string ts;

	for (unsigned int i=0; i<opts.size(); i++) {

		if (hot == int(i)) {
			gfx::color(0,0,0);
			ts = Hot + opts[i];
		}
		else {
			gfx::color(.5, .5, .5);
			ts = Cold + opts[i];
		}
		opt->print(ts.c_str(), x, y + (opt->height() * i));
		if (i < names.size())
			opt->print(names[i].c_str(), x2, y + (opt->height() * i));
	}
}

void config_p1::enter()
{
	setHot(0);
}

void config_p1::exit()
{
}

void config_p1::setHot(int n)
{
	if (n < 0) {
		hot = CP_BACK;
		return;
	}
	if (n > CP_BACK) {
		hot = 0;
		return;
	}
	hot = n;
}

void config_p1::update()
{
	if (capture && input::anykey) {

		int keydef = input::event.key.keysym.sym;
		if (!checkKey(keydef)) {
			bad->play(0,1);
			return;
		}
		select->play(0,1);
		if (hot < (int) names.size()){
			names[hot] = input::keyname(keydef);
			switch (hot) {
				case CP_CONFIRM:
					names[hot] = input::keyname(keydef);
					input::keys[KEY_P1_ACCEPT]->set(keydef);
				break;
				case CP_UP:
					names[hot] = input::keyname(keydef);
					input::keys[KEY_P1_UP]->set(keydef);
				break;
				case CP_DOWN:
					names[hot] = input::keyname(keydef);
					input::keys[KEY_P1_DOWN]->set(keydef);
				break;
				case CP_LEFT:
					names[hot] = input::keyname(keydef);
					input::keys[KEY_P1_LEFT]->set(keydef);
				break;
				case CP_RIGHT:
					names[hot] = input::keyname(keydef);
					input::keys[KEY_P1_RIGHT]->set(keydef);
				break;
			}
		}
		capture = false;
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
	if (input::pressed(KEY_P1_ACCEPT)) {
		if (hot < CP_DEFAULT) {
			capture = true;
			names[hot] = "_";
		}
		else if (hot == CP_DEFAULT) {
			select->play(0,1);
			input::defaultKeys();

			names.clear();
			names.push_back(input::name(KEY_P1_ACCEPT));
			names.push_back(input::name(KEY_P1_UP));
			names.push_back(input::name(KEY_P1_DOWN));
			names.push_back(input::name(KEY_P1_LEFT));
			names.push_back(input::name(KEY_P1_RIGHT));
		}
		else if (hot == CP_BACK) {
			select->play(0,1);
			fsm->change(GS_OPTIONS_MENU);

				fsm->history.pop_back();
		}
		return;
	}
}

bool config_p1::checkKey(int keydef)
{
	if (keydef == input::keys[KEY_P1_ACCEPT]->binding && hot != CP_CONFIRM) return false;
	if (keydef == input::keys[KEY_P1_UP]->binding && hot != CP_UP) return false;
	if (keydef == input::keys[KEY_P1_DOWN]->binding && hot != CP_DOWN) return false;
	if (keydef == input::keys[KEY_P1_LEFT]->binding && hot != CP_LEFT) return false;
	if (keydef == input::keys[KEY_P1_RIGHT]->binding && hot != CP_RIGHT) return false;

	return true;
}

