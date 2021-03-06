#include "audio.h"

	int audio::audio_rate;			//Frequency of audio playback
	Uint16 audio::audio_format;		//Format of the audio we're playing
	int audio::audio_channels;			//2 channels = stereo
	int audio::audio_buffers;		//Size of the audio buffers in memory
	Mix_Music * audio::music;
	soundFactory * audio::sfact;
	playlist audio::songs;
	int audio::lsong = 0;

bool audio::init()
{
//	sran1(SDL_GetTicks());

	sfact = NULL;
	// start SDL with audio support
	if(SDL_InitSubSystem(SDL_INIT_AUDIO) ==- 1) {
		printf("SDL_Init (audio): %s\n", SDL_GetError());
		return false;
	}

	audio_rate = 22050;			//Frequency of audio playback
	audio_format = AUDIO_S16SYS; 	//Format of the audio we're playing
	audio_channels = 2;			//2 channels = stereo
	audio_buffers = 1024;		//Size of the audio buffers in memory

	//Initialize SDL_mixer with our chosen audio settings
	if(Mix_OpenAudio(audio_rate,
							audio_format,
							audio_channels,
							audio_buffers) != 0) {
		printf("Unable to initialize audio: %s\n", Mix_GetError());
		return false;
	}

	// allocate 32 mixing channels
	Mix_AllocateChannels(32);
	sfact = new soundFactory(32);

	music = NULL;
//	Mix_Volume(-1,MIX_MAX_VOLUME * .30);
//	Mix_VolumeMusic(MIX_MAX_VOLUME * .5);

	Mix_HookMusicFinished(song_done);
	songs.load("./data/config/playlist.xml");
//	songs.print();

	return true;

}

void audio::cleanup()
{
	Mix_HaltChannel(-1);
	Mix_HaltMusic();
	free_music();
	if (sfact != NULL)
		delete sfact;
	Mix_CloseAudio();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

void audio::stop_sfx()
{
	Mix_HaltChannel(-1);
}

audio::audio()
{
	// start SDL with audio support
	if(SDL_InitSubSystem(SDL_INIT_AUDIO) ==- 1) {
		printf("SDL_Init (audio): %s\n", SDL_GetError());
	}

	audio_rate = 22050;			//Frequency of audio playback
	audio_format = AUDIO_S16SYS; 	//Format of the audio we're playing
	audio_channels = 2;			//2 channels = stereo
	audio_buffers = 1024;		//Size of the audio buffers in memory

	//Initialize SDL_mixer with our chosen audio settings
	if(Mix_OpenAudio(audio_rate,
							audio_format,
							audio_channels,
							audio_buffers) != 0) {
		printf("Unable to initialize audio: %s\n", Mix_GetError());
	}

	// allocate 32 mixing channels
	Mix_AllocateChannels(32);
	sfact = new soundFactory(32);

	music = NULL;
	Mix_Volume(-1,MIX_MAX_VOLUME * .30);
	Mix_VolumeMusic(MIX_MAX_VOLUME * .5);

}

audio::~audio()
{
	Mix_HaltChannel(-1);
	Mix_HaltMusic();
	free_music();
	delete sfact;
	Mix_CloseAudio();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

int audio::load_music(const char * filename)
{
//	printf("Playing file: %s\n", filename);
	if (music != NULL)
		free_music();

	music = Mix_LoadMUS(filename);

	if(music == NULL) {
		printf("Mix_LoadMUS(%s): %s\n", filename, Mix_GetError());
		return 0;
	}
	return 1;
}

void audio::free_music()
{
	if (music != NULL) {
		Mix_FreeMusic(music);
		music = NULL;
	}
}

int audio::play_music(int loops)
{
	if(Mix_PlayMusic(music, loops) == -1) {
		printf("Mix_PlayMusic: %s\n", Mix_GetError());
		// well, there's no music, but most games don't break without music...
		return 0;
	}

	return 1;
//	return Mix_PlayMusic(music, loops);
}

void audio::stopMusic()
{
	Mix_HaltMusic();
}

void audio::toggleMusic()
{
	if (Mix_PausedMusic())
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();
}

void audio::unpause_music()
{
	Mix_ResumeMusic();
}

void audio::set_sfx_vol(int vol)
{
	Mix_Volume(-1, vol);
}

void audio::set_music_vol(int vol)
{
	Mix_VolumeMusic(vol);
}

sound * audio::load_sfx(const char * filename)
{
	return sfact->load(filename);
}

void audio::song_done()
{
	if (songs.music.size() < 2) {
		if (songs.music.size() == 0)
			return;

		audio::load_music(songs.music[0].second.c_str());
		audio::play_music(0);
		lsong = 0;
		return;
	}

	int i;
	do {
		i = ran1_int(0, songs.music.size());
	} while (i == lsong);
	lsong = i;
	audio::load_music(songs.music[i].second.c_str());
	audio::play_music(0);
}
