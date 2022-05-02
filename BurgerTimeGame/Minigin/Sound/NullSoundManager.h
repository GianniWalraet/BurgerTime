#pragma once
#include "Sound/SoundManager.h"

class NullSoundManager final : public SoundManager
{
public:
	NullSoundManager() = default;
	virtual ~NullSoundManager() override = default;
	NullSoundManager(const NullSoundManager& other) = delete;
	NullSoundManager(NullSoundManager&& other) = delete;
	NullSoundManager& operator=(const NullSoundManager& other) = delete;
	NullSoundManager& operator=(NullSoundManager&& other) = delete;

	void PlayEffect(const soundID, const int, const int, bool) override {}
	void PlayStream(const soundID, const int, const bool) override {}

	virtual void StopStream() override {}
	virtual void ClearEffectQueue() override {}
	virtual void ClearStreamQueue() override {}
};
