#pragma once
#include "IManager.h"
#include <string>
#include <map>


namespace sf
{
	class Music;
	class SoundBuffer;
}
class AudioManager
	: public IManager
{
public:
	virtual int Initialize() override;
	virtual void Release() override;
	virtual void Tick() override;

	bool LoadMusicFromFile(std::string pathName);
	bool LoadSoundFromFile(std::string pathName);

	static AudioManager* Get();

	void Play(std::string musicName);
private:
	std::map<std::string, sf::Music*> m_MusicSets;
	std::map<std::string, sf::SoundBuffer*> m_SoundSets;
	static AudioManager* m_SingleAudioManager;
};

extern AudioManager* g_pAudioManager;