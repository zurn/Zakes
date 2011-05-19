
#include "segment.h"

segment::segment(world * w)
{
	x = y = 0;
	px = py = 0;
	tile_size = w->tile_size;
	velocity = D_NONE;
	pvelocity = D_NONE;
	level = w;
}

segment::~segment() { }

void segment::draw()
{
	gfx::replaceMode();
	gfx::color(0.0,0.0,0.0);
	gfx::drawRect(x*tile_size+1, y*tile_size+1, tile_size-2, tile_size-2);
}

void segment::advance()
{
	px = x;
	py = y;
	pvelocity = velocity;

	if (level->pivots[y][x]!= D_NONE) {
		velocity = level->pivots[y][x];
	}

	switch (velocity) {
		case D_UP: y--; break;
		case D_DOWN: y++; break;
		case D_LEFT: x--; break;
		case D_RIGHT: x++; break;
		case D_NONE: default: break;
	}

	if (x > level->width-1) x = 0;
	if (y > level->height-1) y = 0;
	if (x < 0) x = level->width-1;
	if (y < 0) y = level->height-1;
}

segment::segment() { }

void segment::update() { }

void segment::print()
{
	char * s;
	
	switch (velocity) {
		case D_UP: s = (char*)"up"; break;
		case D_DOWN: s = (char*)"down"; break;
		case D_LEFT: s = (char*)"left"; break;
		case D_RIGHT: s = (char*)"right"; break;
		case D_NONE: s = (char*)"none"; default: break;
	}

	printf("segment\npos %i %i\npre %i %i\nvel %s\n", x,y,px,py,s);
}

