#include "AudioManager.h"
#include "SFML/Audio.hpp"

#include	<cstdio>
#include	<cstring>


sf::Music g_music;

AudioManager* AudioManager::mSingleAudioManager = nullptr;

int AudioManager::Initialize()
{
	return 0;
}

void AudioManager::Release()
{
	delete mSingleAudioManager;
}

void AudioManager::Tick()
{
}

int AudioManager::LoadMusicFromFile(std::string pathName)
{
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



