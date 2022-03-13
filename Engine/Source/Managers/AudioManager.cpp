#include "AudioManager.h"
#include "SFML/Audio.hpp"
#include "ResourceManager.h"

#include	<cstdio>
#include	<cstring>

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
	sf::Music music;
	music.openFromFile(pathName.data());
	return 0;
}

int AudioManager::LoadSoundFromFile(std::string pathName)
{
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

void AudioManager::Play(std::string musicName)
{
	mMusicSets[musicName]->play();
}



