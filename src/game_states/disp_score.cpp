
#include "disp_score.h"

disp_score::disp_score(game * fsm)
{
	selected = SLOW;
	disp_score::fsm = fsm;

	opt = gfx::loadFont("./data/fonts/mono.ttf", 20);
	opt2 = gfx::loadFont("./data/fonts/mono.ttf", 36);
	title = gfx::loadFont("./data/fonts/mono.ttf", 44);
	select = audio::loadSfx("./data/sfx/select.wav");
	move = audio::loadSfx("./data/sfx/omove.wav");
}

disp_score::~disp_score()
{
}

void disp_score::enter()
{
	selected = fsm->custom->speed;
}

void disp_score::exit()
{
}

void disp_score::draw()
{

	gfx::blendMode();
	gfx::color(0,0,0);
	std::string name("High Scores");
	int xpos = 320 - (title->width(name.c_str())/2);
	int ypos = 53;
	title->print(name.c_str(), xpos, ypos);

	int x = 16*6, y = 16*10;
	int x2 = 16 *28;

	const char * msg = "";
	switch (selected) {
		case DS_SLOW:
			msg = "Slow";
			draw(fsm->high_score->slow_scores, x, y);
		break;
		case DS_MEDIUM:
			msg = "Medium";
			draw(fsm->high_score->medium_scores, x, y);
		break;
		case DS_FAST:
			msg = "Fast";
			draw(fsm->high_score->fast_scores, x, y);
		break;
	}
	opt2->print(msg, 320-(opt2->width(msg)/2), y -20 -  opt2->height());
	opt->print("Name ", x, y-21);
	opt->print("Score", x2, y-21);
	opt->print("<", 10, 249);
	opt->print(">", 630 - opt->width(">"), 249);
}

void disp_score::draw(std::vector<entry> & entries, int x, int y)
{
	for (unsigned int i=0; i<entries.size(); i++) {
		char buf[256];
		buf[255] = '\0';

		snprintf(buf, sizeof(buf), "%i%s%s", i+1, ": ",  entries[i].name.c_str());
//		opt->print(entries[i].name.c_str(), x, y + (opt->height() * i));
		opt->print(buf, x, y + (opt->height() * i));
		snprintf(buf, sizeof(buf), "%i", entries[i].score);

		opt->print(buf, 16 * 28, y + (opt->height() * i));
		
	}

}

void disp_score::update()
{
	if (input::pressed(KEY_P1_LEFT)) {
		selected--;
		if (selected < DS_SLOW) {
			selected = DS_FAST;
		}
		select->play(0,1);
	}
	if (input::pressed(KEY_P1_RIGHT)) {
		selected++;
		if (selected > DS_FAST) {
			selected = DS_SLOW;
		}
		select->play(0,1);
	}
	if (input::pressed(KEY_P1_ACCEPT) ) {
		fsm->change(GS_MAIN_MENU);
	}
}

