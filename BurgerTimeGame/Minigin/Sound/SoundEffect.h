#pragma once
#include "SoundEffect.h"
#include <string>

class SoundEffect final
{
public:
	explicit SoundEffect(const std::string& path);
	~SoundEffect();
	SoundEffect(const SoundEffect& other) = delete;
	SoundEffect& operator=(const SoundEffect& rhs) = delete;
	SoundEffect(SoundEffect&& other) = delete;
	SoundEffect& operator=(SoundEffect&& rhs) = delete;

	void Load();
	bool IsLoaded() const;

	bool Play(int loops) const;

	void SetVolume(int value);
	int GetVolume();
private:
	class SoundEffectImpl;
	SoundEffectImpl* m_pImpl;
};

