#include "MiniginPCH.h"
#include "SoundEffect.h"
#include "SDL_mixer.h"


class SoundEffect::SoundEffectImpl
{
public:
	explicit SoundEffectImpl(const std::string& path);
	~SoundEffectImpl();
	SoundEffectImpl(const SoundEffectImpl& other) = delete;
	SoundEffectImpl& operator=(const SoundEffectImpl& rhs) = delete;
	SoundEffectImpl(SoundEffectImpl&& other) = delete;
	SoundEffectImpl& operator=(SoundEffectImpl&& rhs) = delete;

	void Load();
	bool IsLoaded() const;

	void Play(int loops);
	bool IsPlaying();

	void SetVolume(int value);
	int GetVolume();
private:
	Mix_Chunk* m_pMixChunk{};
	int m_ActiveChannel{};
	std::string m_Path{};
};


SoundEffect::SoundEffect(const std::string& path)
{
	m_pImpl = new SoundEffectImpl(path);
}
SoundEffect::~SoundEffect()
{
	delete m_pImpl;
}
void SoundEffect::Load()
{
	m_pImpl->Load();
}
bool SoundEffect::IsLoaded() const
{
	return m_pImpl->IsLoaded();
}
void SoundEffect::Play(int loops)
{
	m_pImpl->Play(loops);
}
bool SoundEffect::IsPlaying()
{
	return m_pImpl->IsPlaying();
}
void SoundEffect::SetVolume(int value)
{
	m_pImpl->SetVolume(value);
}
int SoundEffect::GetVolume()
{
	return m_pImpl->GetVolume();
}

SoundEffect::SoundEffectImpl::SoundEffectImpl(const std::string& path)
	: m_Path{ path }
	, m_pMixChunk{}
{
}
SoundEffect::SoundEffectImpl::~SoundEffectImpl()
{
	if (IsLoaded())
	{
		Mix_FreeChunk(m_pMixChunk);
		m_pMixChunk = nullptr;
	}
}
void SoundEffect::SoundEffectImpl::Load()
{
	if(!IsLoaded()) m_pMixChunk = Mix_LoadWAV(m_Path.c_str());

	if (m_pMixChunk == nullptr)
	{
		std::string errorMsg = "SoundEffect: Failed to load " + m_Path + ",\nSDL_mixer Error: " + Mix_GetError();
		std::cerr << errorMsg;
	}
}
bool SoundEffect::SoundEffectImpl::IsLoaded() const
{
	return m_pMixChunk != nullptr;
}
void SoundEffect::SoundEffectImpl::Play(int loops)
{
	if (m_pMixChunk != nullptr)
	{
		m_ActiveChannel = Mix_PlayChannel(-1, m_pMixChunk, loops);
	}
}
bool SoundEffect::SoundEffectImpl::IsPlaying()
{
	return Mix_Playing(m_ActiveChannel) == 0 ? false : true;
}
void SoundEffect::SoundEffectImpl::SetVolume(int value)
{
	if (m_pMixChunk != nullptr)
	{
		Mix_VolumeChunk(m_pMixChunk, value);
	}
}
int SoundEffect::SoundEffectImpl::GetVolume()
{
	if (m_pMixChunk != nullptr)
	{
		return Mix_VolumeChunk(m_pMixChunk, -1);
	}
	else
	{
		return -1;
	}
}
