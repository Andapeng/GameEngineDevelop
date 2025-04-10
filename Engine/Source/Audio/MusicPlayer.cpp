#include "MusicPlayer.h"
#include "SFML/Audio/Music.hpp"
#include "../Log.h"

MusicPlayer::MusicPlayer()
	:mMusic(std::make_shared<sf::Music>())
{
}

void MusicPlayer::Play(std::string_view filePath)
{
	LoadMusicFromFile(filePath);
	mMusic->play();
}

void MusicPlayer::LoadMusicFromFile(std::string_view filePath)
{
	if (!mMusic->openFromFile(filePath.data()))
	{
		Logger::LogError("Load Music From File Failed.");
	}
}
