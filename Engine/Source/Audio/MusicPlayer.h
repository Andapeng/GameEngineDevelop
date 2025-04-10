#pragma once
#include <memory>
#include <string_view>
namespace sf
{
	class Music;
}

class MusicPlayer
{
public:
	MusicPlayer();
	void Play(std::string_view filePath);
private:
	void LoadMusicFromFile(std::string_view filePath);

	std::shared_ptr<sf::Music> mMusic;
};
