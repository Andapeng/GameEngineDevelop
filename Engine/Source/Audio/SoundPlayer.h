#pragma once
#include <map>
#include <memory>
#include "SFML/Audio/SoundBuffer.hpp"

class SoundPlayer
{
public:
	SoundPlayer();
	void Play(std::string_view filePath);
private:
	void LoadSoundFromFile(std::string_view filePath);

	std::shared_ptr<sf::Sound> mSound;
	std::map<std::string, std::shared_ptr<sf::SoundBuffer>> mSoundBuffers;
};