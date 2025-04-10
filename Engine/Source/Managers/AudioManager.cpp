#include "AudioManager.h"
#include "SFML/Audio.hpp"
#include "ResourceManager.h"

#include "../Audio/MusicPlayer.h"
#include "../Audio/SoundPlayer.h"
AudioManager* AudioManager::mSingleAudioManager = nullptr;

int AudioManager::Initialize()
{
	mMusicPlayer = std::make_shared<MusicPlayer>();
	mSoundPlayer = std::make_shared<SoundPlayer>();
	return 0;
}

void AudioManager::Release()
{
	delete mSingleAudioManager;
}

void AudioManager::Tick()
{
}

AudioManager* AudioManager::Get()
{
	if (mSingleAudioManager == nullptr)
	{
		mSingleAudioManager = new AudioManager;
	}
	return mSingleAudioManager;
}


