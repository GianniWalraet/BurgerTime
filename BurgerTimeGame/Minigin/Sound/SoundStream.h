#pragma once
#include "SoundStream.h"

class SoundStream final
{
public:
	SoundStream(const std::string& path);
	virtual ~SoundStream();

	void Load();
	bool IsLoaded();

	bool Play(bool repeat);
	void Pause();
	void Stop();
	bool IsPlaying();

	void SetVolume(int value);
	int GetVolume();
private:
	class SoundStreamImpl;
	SoundStreamImpl* m_pImpl;
};

