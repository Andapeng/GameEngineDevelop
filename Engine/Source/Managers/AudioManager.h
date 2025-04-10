#pragma once
#include "IManager.h"
#include <string>
#include <map>
#include <memory>

#include "../Audio/MusicPlayer.h"

class SoundPlayer;
class MusicPlayer;

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

	static AudioManager* Get();

	std::shared_ptr<MusicPlayer> GetMusicPlayer() { return mMusicPlayer; }
	std::shared_ptr<SoundPlayer> GetSoundPlayer() { return mSoundPlayer; }
private:
	std::shared_ptr<MusicPlayer> mMusicPlayer = nullptr;
	std::shared_ptr<SoundPlayer> mSoundPlayer = nullptr;
	static AudioManager* mSingleAudioManager;
};

extern AudioManager* g_pAudioManager;