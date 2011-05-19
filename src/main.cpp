
#include "zlibengn.h"
#include "audio.h"
#include "gfx.h"
#include "input.h"
#include "settings.h"
#include "timer.h"
#include "game.h"	

//main game loop

int main(int argc, char * argv[])
{
	gfx::init();

	sran1(SDL_GetTicks()% (SDL_GetTicks()*256));
	sran1(ran1()*1000);

	input::init();
	audio::init();

//	Mix_Volume(-1,MIX_MAX_VOLUME * .1);
//	Mix_VolumeMusic(MIX_MAX_VOLUME * .05);

//	ZlibEngine z;
//	z.compress( "data/controls.xml","controls.xml.z");
//	z.decompress( "controls.xml.z", "thing.xml");

	timer fps(60);
	sran1(SDL_GetTicks()% (SDL_GetTicks()*256));
	audio::song_done();

	settings * local = new settings("./data/config/settings.xml");
//	game rlzair(local);
	game snake(local);

//	local->save("temp.xml");

	while (!input::quit) {

		input::poll();
		input::update();
//
//		if (input::pressed(KEY_DBG_SHOT)) {
//			gfx::BMPshot((char *)"shot.bmp");
//		}
//		if (input::pressed(KEY_DBG_QUIT)) {
//			input::quit = true;
//		}
//		if (input::pressed(KEY_DBG_1)) {
//			audio::song_done();
//		}
		snake.update();

		gfx::clear();

		snake.draw();

		gfx::swap();
		fps.delay();
	}

	local->save("./data/config/settings.xml");
	snake.cleanup();
//	local->print();
	delete local;

	input::cleanup();
	audio::cleanup();
	gfx::cleanup();

	return 0;
}

