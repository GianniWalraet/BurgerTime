#pragma once
#include "SoundEffect.h"

class Mix_Chunk;

class SDLSoundEffect final : SoundEffect
{
public:
	explicit SDLSoundEffect(const std::string& path);
	virtual ~SDLSoundEffect() override;
	SDLSoundEffect(const SDLSoundEffect& other) = delete;
	SDLSoundEffect& operator=(const SDLSoundEffect& rhs) = delete;
	SDLSoundEffect(SDLSoundEffect&& other) = delete;
	SDLSoundEffect& operator=(SDLSoundEffect&& rhs) = delete;

	bool IsLoaded() const override;
	void Play() const override;
	void SetVolume(int value) override;
private:
	Mix_Chunk* m_pMixChunk;
};

