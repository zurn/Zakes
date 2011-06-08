#ifndef AUDIO_DOT_H
#define AUDIO_DOT_H

#include "SDL.h"
#include "soundFactory.h"
#include "playlist.h"
#include "RNG.h"

class audio
{
	private:
		audio();
		~audio();

	public:
		static bool init();
		static void cleanup();
		static int load_music(const char * filename);
		static void free_music();



		static void song_done();
		static int play_music(int loops);
		static void toggleMusic();
		static void stopMusic();
		static void stop_sfx();
		static void set_music_vol(int vol);
		static void set_sfx_vol(int vol);
		static void unpause_music();

		static sound * load_sfx(const char * filename);

		static int audio_rate;			//Frequency of audio playback
		static Uint16 audio_format;		//Format of the audio we're playing
		static int audio_channels;			//2 channels = stereo
		static int audio_buffers;		//Size of the audio buffers in memory

	private:
		static Mix_Music * music;
		static soundFactory * sfact;
		static playlist songs;
		static int lsong;
};

#endif

