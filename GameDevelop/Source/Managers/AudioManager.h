#pragma once
#include "IManager.h"
#include <OpenAL/include/alc.h>
#include <string>
class AudioManager
	: public IManager
{
public:
	virtual int Initialize() override;
	virtual void Release() override;
	virtual void Tick() override;

	int LoadMusicFromFile(std::string pathName);

	static AudioManager* Get();

	void Play();
private:
	ALCdevice* mDevice;
	ALCcontext* mContext;

	static AudioManager* mSingleAudioManager;
};

extern AudioManager* g_pAudioManager;