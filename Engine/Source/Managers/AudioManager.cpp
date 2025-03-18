#include "AudioManager.h"
#include "SFML/Audio.hpp"
#include "ResourceManager.h"

#include "../Log.h"
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

bool AudioManager::LoadMusicFromFile(std::string pathName)
{
	sf::Music music;
	if (!music.openFromFile(pathName))
	{
		Logger::LogError("Load Music From File Failed.");
	}
	return true;
}

bool AudioManager::LoadSoundFromFile(std::string pathName)
{
	sf::SoundBuffer soundBuffer;
	if (!soundBuffer.loadFromFile(pathName))
	{
		Logger::LogError("Load Sound From File Failed.");
	}
	return true;
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



