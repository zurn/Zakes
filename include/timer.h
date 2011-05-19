#ifndef TIMER
#define TIMER

#include "SDL.h"
//#include "SDL_opengl.h"



class timer
{
	public:
		timer();
		timer(int fps);
		~timer();

		void delay();
		void setFPS(int rate);


		int frame;
		int last;
		int fps;
		int fps_ticks;
};

#endif

