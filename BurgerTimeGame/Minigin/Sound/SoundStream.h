#pragma once


class SoundStream abstract
{
public:
	SoundStream() = default;
	virtual ~SoundStream() = default;

	virtual void Load() = 0;
	virtual bool IsLoaded() = 0;

	virtual void Play() = 0;
	virtual void Pause() = 0;
	virtual void Stop() = 0;
	virtual bool IsPlaying() = 0;
private:
};

