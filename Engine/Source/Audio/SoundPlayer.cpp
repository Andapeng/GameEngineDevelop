#include "SoundPlayer.h"

#include <format>
#include <SFML/Audio/Sound.hpp>

#include "../Log.h"

SoundPlayer::SoundPlayer()
	:mSound(std::make_shared<sf::Sound>())
{
}

void SoundPlayer::LoadSoundFromFile(std::string_view filePath)
{
	std::shared_ptr<sf::SoundBuffer> soundBuffer = std::make_shared<sf::SoundBuffer>();
	if (!soundBuffer->loadFromFile(filePath.data()))
	{
		Logger::LogError("Load Sound From File Failed.");
	}
	mSoundBuffers[filePath.data()] = soundBuffer;
}

void SoundPlayer::Play(std::string_view filePath)
{
	LoadSoundFromFile(filePath);
	if (mSoundBuffers.contains(filePath.data()))
	{
		mSound->setBuffer(*mSoundBuffers[filePath.data()]);
		mSound->play();
	}

}
