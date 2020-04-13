#include "AudioManager.h"
#include <AL/al.h>
#include <sndfile.hh>
#include "SFML/Audio.hpp"

#include	<cstdio>
#include	<cstring>

#define		BUFFER_LEN		1024

sf::Music g_music;

AudioManager* AudioManager::mSingleAudioManager = nullptr;

static void
create_file(const char* fname, int format)
{
	static short buffer[BUFFER_LEN];

	SndfileHandle file;
	int channels = 2;
	int srate = 48000;

	printf("Creating file named '%s'\n", fname);

	file = SndfileHandle(fname, SFM_WRITE, format, channels, srate);

	memset(buffer, 0, sizeof(buffer));

	file.write(buffer, BUFFER_LEN);

	puts("");
	/*
	**	The SndfileHandle object will automatically close the file and
	**	release all allocated memory when the object goes out of scope.
	**	This is the Resource Acquisition Is Initailization idom.
	**	See : http://en.wikipedia.org/wiki/Resource_Acquisition_Is_Initialization
	*/
} /* create_file */

static void
read_file(const char* fname)
{
	static short buffer[BUFFER_LEN];

	SndfileHandle file;

	file = SndfileHandle(fname);

	printf("Opened file '%s'\n", fname);
	printf("    Sample rate : %d\n", file.samplerate());
	printf("    Channels    : %d\n", file.channels());

	file.read(buffer, BUFFER_LEN);

	puts("");

	/* RAII takes care of destroying SndfileHandle object. */
} /* read_file */


int AudioManager::Initialize()
{
	//mDevice = alcOpenDevice(nullptr);
	//if (mDevice) {
	//	mContext = alcCreateContext(mDevice, nullptr);
	//	alcMakeContextCurrent(mContext);
	//}	
	
	puts("\nSimple example showing usage of the C++ SndfileHandle object.\n");

	const char* fname = "MusicCreate";

	create_file(fname, SF_FORMAT_WAV | SF_FORMAT_PCM_16);

	read_file(fname);

	puts("Done.\n");

	return 0;
}

void AudioManager::Release()
{
	//alcMakeContextCurrent(NULL);
	//alcDestroyContext(mContext);
	//alcCloseDevice(mDevice);
	
	delete mSingleAudioManager;
}

void AudioManager::Tick()
{
}

int AudioManager::LoadMusicFromFile(std::string pathName)
{
	//loadWAVFile("test.wav", &format, &data, &size, &freq, &loop);
	g_music.openFromFile(pathName.data());
	return 0;
}

AudioManager* AudioManager::Get()
{
	if (mSingleAudioManager == nullptr)
	{
		mSingleAudioManager = new AudioManager;
	}
	return mSingleAudioManager;
}

void AudioManager::Play()
{
	g_music.play();
}



