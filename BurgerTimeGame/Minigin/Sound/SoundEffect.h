#pragma once


class SoundEffect abstract
{
public:
	SoundEffect() = default;
	virtual ~SoundEffect() = default;

	virtual void Load() = 0;
	virtual bool IsLoaded() const = 0;

	virtual void Play() const = 0;

	virtual void SetVolume(int volume) = 0;
private:

};

