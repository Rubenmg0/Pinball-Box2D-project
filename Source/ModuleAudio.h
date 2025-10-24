#pragma once

#include "Module.h"

#define MAX_SOUNDS	16
#define DEFAULT_MUSIC_FADE_TIME 2.0f

class ModuleAudio : public Module
{
public:

	ModuleAudio(Application* app, bool start_enabled = true);
	~ModuleAudio();

	bool Init();
	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);
	void StopMusic();
	Music GetMusic() { return music; };

	// Load a sound in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded sound
	bool PlayFx(unsigned int fx, int repeat = 0);
public:
	bool musicOn = true;
	bool soundsOn = true;

private:

	Music music;
	Sound fx[MAX_SOUNDS];
    unsigned int fx_count;
};
