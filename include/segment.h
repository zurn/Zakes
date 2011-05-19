
#ifndef __SEGMENT_H__
#define __SEGMENT_H__

#include "gfx.h"
#include "RNG.h"
#include "world.h"
#include "direction.h"

class segment
{
	public:
		segment(world * w);
		virtual ~segment();

		void advance();
		void update();
		void draw();
		void print();

		int x,y; //level grid coordinates
		int px, py; //last x,y positions
		int tile_size;
		direction velocity;
		direction pvelocity;
		world * level;
	private:
		segment();

};
#endif /* __SEGMENT_H__ */
