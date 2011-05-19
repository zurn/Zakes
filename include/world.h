
#ifndef __WORLD_H__
#define __WORLD_H__

#include "gfx.h"
#include "grid.h"
#include "direction.h"

#include <iostream>

class world
{
	public:
		world();
		virtual ~world();

		void update();
		void draw();

		void print();
		bool load(const char * filename);
		bool init(const char * filename);
		void getFree(int & x, int & y);

		void drawChar(const char * c, int x, int y);

		bool is_valid();
		//returns true if the level is beatable
		//returns false otherwise

		bool valid(int x, int y);
		bool is_valid(int x, int y);
//	private:
		grid * walls;
		grid * cherries;
		std::vector<std::vector<direction> > pivots;

		int width;
		int height;
		int tile_size;

};
#endif /* __WORLD_H__ */
