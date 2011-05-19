
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "segment.h"
#include "world.h"
#include "input.h"
#include "audio.h"

#include <list>

#define SPEED_SLOW 90;
#define SPEED_MEDIUM 50;
#define SPEED_FAST 20;

class player
{
	public:
		player(world * w);
		virtual ~player();

		void update();
		void draw();

		void print();
		void add_segment();
		void reset();
		bool collide(int x, int y);
		//returns true if x,y is inside the body or head
		//false otherwise

		const char * name;
		world * level;
		segment * head;
		segment * tail;
		std::list<segment *> body;
		int last_advance;
		int advance_delay;
		direction last_vel;
		int cherry_count;

		sound * cherry;
		sound * hit;
		bool dead;
		bool grew;
	private:
		player();

};
#endif /* __PLAYER_H__ */
