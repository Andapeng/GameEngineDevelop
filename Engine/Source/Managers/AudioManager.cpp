#include "AudioManager.h"
#include "SFML/Audio.hpp"
#include "ResourceManager.h"

#include <boost/log/trivial.hpp>

AudioManager* AudioManager::m_SingleAudioManager = nullptr;

int AudioManager::Initialize()
{
	
	return 0;
}

void AudioManager::Release()
{
	delete m_SingleAudioManager;
}

void AudioManager::Tick()
{
}

bool AudioManager::LoadMusicFromFile(std::string pathName)
{
	sf::Music music;
	if (!music.openFromFile(pathName))
	{
		BOOST_LOG_TRIVIAL(error) << "Load Music From File Failed.";
	}
	return true;
}

bool AudioManager::LoadSoundFromFile(std::string pathName)
{
	sf::SoundBuffer soundBuffer;
	if (!soundBuffer.loadFromFile(pathName))
	{
		BOOST_LOG_TRIVIAL(error) << "Load Sound From File Failed.";
	}
	return true;
}

AudioManager* AudioManager::Get()
{
	if (m_SingleAudioManager == nullptr)
	{
		m_SingleAudioManager = new AudioManager;
	}
	return m_SingleAudioManager;
}

void AudioManager::Play(std::string musicName)
{
	m_MusicSets[musicName]->play();
}



