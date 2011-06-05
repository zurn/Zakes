
#include "player.h"

player::player(world * w)
{
	name = "";
	grew = false;
	dead = false;
	level = w;
	head = new segment(level);
	tail = head;
	advance_delay = SPEED_SLOW;
	last_advance = SDL_GetTicks() + advance_delay;
	last_vel = D_DOWN;
	head->px = head->py = -1;
//	head->x = ran1_int(0,level->width);
//	head->y = ran1_int(0,level->height);
	level->getFree(head->x, head->y);
	cherry = audio::load_sfx("./data/sfx/cherry.wav");
	hit = audio::load_sfx("./data/sfx/hit.wav");
	cherry_count = 0;
}

player::~player()
{
	delete head;

	for (std::list<segment*>::iterator it=body.begin(); it!=body.end(); ++it) {
		delete (*it);
	}
	body.clear();
}

void player::draw()
{
	head->draw();

	for (std::list<segment*>::iterator it=body.begin(); it!=body.end(); ++it) {
		(*it)->draw();
	}

	font * text = gfx::load_font("./data/fonts/mono.ttf", 18);
	
	gfx::blendMode();
	gfx::color(0,0,0);
	char buf[256];
	buf[255] = '\0';
	snprintf(buf, sizeof(buf), "%s%i", "Score: ", cherry_count);

	text->print(buf, 2 ,463);
}

void player::update()
{
	if (input::pressed(KEY_P1_UP) && head->pvelocity != D_DOWN) {
		head->velocity = D_UP;
	}

	if (input::pressed(KEY_P1_DOWN) && head->pvelocity != D_UP) {
		head->velocity = D_DOWN;
	}

	if (input::pressed(KEY_P1_LEFT) && head->pvelocity != D_RIGHT) {
		head->velocity = D_LEFT;
	}

	if (input::pressed(KEY_P1_RIGHT) && head->pvelocity != D_LEFT) {
		head->velocity = D_RIGHT;
	}

	int now = SDL_GetTicks();
	if (now - last_advance > advance_delay  ) {

//		printf("advance snake\n");

		head->advance();
		for (std::list<segment*>::iterator it=body.begin(); it!=body.end(); ++it) {
			(*it)->advance();
		}
		if (head->velocity != last_vel) {
			level->pivots[head->py][head->px] = head->velocity;
			last_vel = head->velocity;
		}
		if ((*level->walls)(head->x, head->y)) {
//			printf("game over\n");
			hit->play(0,1);
			dead = true;
			return;
		}
		for (std::list<segment*>::iterator it=body.begin(); it!=body.end(); ++it) {
			if ((*it)->x == head->x && (*it)->y == head->y){
				hit->play(0,1);
				dead = true;
				return;
			}
		}
		if ((*level->cherries)(head->x, head->y) == 1) {
			(*level->cherries)(head->x, head->y) = 0;
			cherry->play(0,1);
			add_segment();
			grew = true;
		}
		if (tail != NULL) {
			level->pivots[tail->py][tail->px] = D_NONE;
		}
		last_advance = now;
	}
}

player::player() { }

void player::add_segment()
{
	segment * target = NULL;
	int x,y;

	if (body.size() < 1) {
		target = head;
		x = target->x;
		y = target->y;
	}
	else {
//		target = body.back();
		target = tail;
		x = target->x;
		y = target->y;
	}

	switch (target->velocity) {

		case D_UP: y++; break;
		case D_DOWN: y--; break;
		case D_LEFT: x++; break;
		case D_RIGHT: x--; break;
		case D_NONE: printf("how did this happen\n\n"); default: break;

	}


	if (x > level->width-1) x = 0;
	if (y > level->height-1) y = 0;
	if (x < 0) x = level->width-1;
	if (y < 0) y = level->height-1;

	segment * temp;
	temp = new segment(level);
	temp->x = x;
	temp->y = y;
	temp->velocity = target->velocity;
	body.push_back(temp);
//	printf("added segment %i\n", body.size());
	tail = temp;
}

void player::reset()
{
	delete head;

	for (std::list<segment*>::iterator it=body.begin(); it!=body.end(); ++it) {
		delete (*it);
	}
	body.clear();

	dead = false;
	head = new segment(level);

	tail = head;
//	last_vel = D_NONE;
//	head->x = ran1_int(0,level->width);
//	head->y = ran1_int(0,level->height);
	head->px = head->py = -1;
	level->getFree(head->x, head->y);
	last_advance = SDL_GetTicks() + advance_delay;
	cherry_count = 0;
}

bool player::collide(int x, int y)
{
	if (head->x ==x && head->y == y) return true;
	for (std::list<segment*>::iterator it=body.begin(); it!=body.end(); ++it) {
		if ((*it)->x == x && (*it)->y == y){
			return true;
		}
	}
	return false;
}

void player::print()
{
	printf("begin player print\n\n");
	head->print();
	for (std::list<segment*>::iterator it=body.begin(); it!=body.end(); ++it) {
		(*it)->print();
	}
	printf("end player print\n\n");
}

