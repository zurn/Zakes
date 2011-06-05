
#include "world.h"

world::world()
{
//	walls = new grid(40, 30, 0);
//	printf("world const\n");
	walls = NULL;
	cherries = NULL;
	width = height = tile_size = 0;
}

world::~world()
{
	if (walls != NULL) {
		delete walls;
	}
	if (cherries != NULL) {
		delete cherries;
	}
}

void world::drawChar(const char * c, int x, int y)
{
	gfx::blendMode();
	gfx::color(0,0,1);
	gfx::load_font("./data/fonts/mono.ttf", 14)->print(c, x*tile_size, y*tile_size);
}

void world::draw()
{
	if (walls == NULL) return;
	gfx::blendMode();
//	gfx::replaceMode();

	for (int w=0; w<walls->width; w++) {
		for (int h=0; h<walls->height; h++) {
			if ((*walls)(w,h) == 0) {
//				gfx::color(.5,.5,.5);
//				gfx::drawFrame(w*tile_size+1, h*tile_size+1, tile_size, tile_size, 1);
			}
			else {
				gfx::color(.5,.5,.5);
				gfx::drawRect(w*tile_size, h*tile_size, tile_size, tile_size);
//				gfx::drawRect(w*tile_size+1, h*tile_size+1, tile_size-2, tile_size-2);
			}
		}
	}

	//debuging draw pivot directions
	if (!1) {
		for (int w=0; w<walls->width; w++) {
			for (int h=0; h<walls->height; h++) {
				switch (pivots[h][w] ) {
					case D_UP: drawChar("u",w, h); break;
					case D_DOWN: drawChar("d",w, h); break;
					case D_LEFT: drawChar("l",w, h); break;
					case D_RIGHT: drawChar("r",w, h); break;
					case D_NONE: default: break;
				}
			}
		}
	}


	for (int w=0; w<cherries->width; w++) {
		for (int h=0; h<cherries->height; h++) {
			if ((*cherries)(w,h) == 1) {
				gfx::color(1,.0,.0);
				gfx::drawRect(w*tile_size+1, h*tile_size+1, tile_size-2, tile_size-2);
			}
		}
	}
}

void world::update()
{
}

bool world::load(const char * filename)
{
	return true;
}

bool world::init(const char * filename)
{

	width = 40;
	height = 29;
	tile_size = 16;

	if (walls != NULL) {
		delete walls;
	}

	walls = new grid(width, height, 0);
	walls->fill = 1;

	walls->line(0,0,39,0);
	walls->line(0,0,0,28);
	walls->line(0,28,39,28);
	walls->line(39,0,39,28);

//	walls->line(13,14,30,14);
//	walls->line(3,4,20,4);
//	walls->line(23,24,37,24);

//	int num_lines = ran1_dice(3, 6);
	int num_lines = poisson_rand(8.0);
	while (num_lines < 5 || num_lines > 12) {
		num_lines = ran1_int(5,12);
	}
//	printf("num random walls %i\n", num_lines);
//	num_lines = 11;
	for (int i=0; i<num_lines; i++) {
		int d = ran1_dice(2, 4);
		int x = ran1_int(1, width-1);
		int y = ran1_int(1, height-1);

		int w,h;
		if (ran1_int(0,2)==1) {
			if (ran1_int(0,2)==1) {
				w = x + d;
			}
			else {
				w = x - d;
			}
			h = y;
		}
		else {
			w = x;
			if (ran1_int(0,2)==1) {
				h = y - d;
			}
			else {
				h = y + d;
			}
		}

		walls->line(x,y,w,h);

	}

	if (cherries != NULL) {
		delete cherries;
	}
	cherries = new grid(width, height, 0);




	pivots.clear();
	std::vector<direction> row(width, D_NONE);

	for (int i=0; i<height; i++) {
		pivots.push_back(row);
	}
//
//	if (!is_valid()) {
//		printf("level is unbeatable\n");
//	}
//	else {
//		printf("level is good\n");
//	}
	return is_valid();
}

bool world::is_valid(int x, int y)
{
	if (walls->bounds(x,y)) {
		if ((*walls)(x,y) == 1) {
			return true;
		}
	}
	int wall_count = 0;
	int nx = x;
	int ny = y;

	nx--;
	if (valid(nx, ny)) {
		if ((*walls)(nx, ny) == 1) {
			wall_count++;
		}
	}

	nx = x;
	ny = y;
	nx++;

	if (valid(nx, ny)) {
		if ((*walls)(nx, ny) == 1) {
			wall_count++;
		}
	}

	nx = x;
	ny = y;
	ny++;

	if (valid(nx, ny)) {
		if ((*walls)(nx, ny) == 1) {
			wall_count++;
		}
	}

	nx = x;
	ny = y;
	ny--;

	if (valid(nx, ny)) {
		if ((*walls)(nx, ny) == 1) {
			wall_count++;
		}
	}

	if (wall_count > 2)
		return false;
	else
		return true;
}

bool world::valid(int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
		return true;
	else
		return false;
}


bool world::is_valid()
{
	for (int y=0; y<height; y++) {
		for (int x=0; x<width; x++) {
			if (!is_valid(x, y))
				return false;
		}
	}
	return true;
}

void world::print()
{
	printf("world info\nw: %i h: %i\ntile: %i\n", width, height, tile_size);
}

void world::getFree(int & x, int & y)
{
	if (walls == NULL || cherries == NULL) {
//		printf("fooy\n");
		return;
	}
	do {
		x = ran1_int(0, walls->width);
		y = ran1_int(0, walls->height);
	} while ((*walls)(x,y)==1 ||
			(*cherries)(x,y)==1 
	);
}

