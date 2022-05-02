#include "MiniginPCH.h"
#include "SoundStream.h"
#include <thread>
#include <condition_variable>

class SoundStream::SoundStreamImpl
{
public:
	SoundStreamImpl(const std::string& path);
	~SoundStreamImpl();

	void Load();
	bool IsLoaded();

	bool Play(bool repeat);
	void Pause();
	void Stop();
	bool IsPlaying();

	void SetVolume(int value);
	int GetVolume();
private:
	std::string m_Path{};
	Mix_Music* m_pMixMusic{};
};


SoundStream::SoundStream(const std::string& path)
{
	m_pImpl = new SoundStreamImpl(path);
}
SoundStream::~SoundStream()
{
	delete m_pImpl;
}
void SoundStream::Load()
{
	m_pImpl->Load();
}
bool SoundStream::IsLoaded()
{
	return m_pImpl->IsLoaded();
}
bool SoundStream::Play(bool repeat)
{
	return m_pImpl->Play(repeat);
}
void SoundStream::Pause()
{
	m_pImpl->Pause();
}
void SoundStream::Stop()
{
	m_pImpl->Stop();
}
bool SoundStream::IsPlaying()
{
	return m_pImpl->IsPlaying();
}
void SoundStream::SetVolume(int value)
{
	m_pImpl->SetVolume(value);
}
int SoundStream::GetVolume()
{
	return m_pImpl->GetVolume();
}


SoundStream::SoundStreamImpl::SoundStreamImpl(const std::string& path)
	: m_Path{ path }
{}
SoundStream::SoundStreamImpl::~SoundStreamImpl()
{
	if (IsLoaded())
	{
		Mix_FreeMusic(m_pMixMusic);
		m_pMixMusic = nullptr;
	}
}
void SoundStream::SoundStreamImpl::Load()
{
	if (!IsLoaded()) m_pMixMusic = Mix_LoadMUS(m_Path.c_str());

	if (m_pMixMusic == nullptr)
	{
		std::string errorMsg = "SoundStream: Failed to load " + m_Path + ",\nSDL_mixer Error: " + Mix_GetError();
		std::cerr << errorMsg;
	}
}
bool SoundStream::SoundStreamImpl::IsLoaded()
{
	return m_pMixMusic != nullptr;
}
bool SoundStream::SoundStreamImpl::Play(bool repeat)
{
	if (m_pMixMusic != nullptr)
	{
		int result{ Mix_PlayMusic(m_pMixMusic, repeat ? -1 : 1) };
		std::cout << Mix_GetError();
		return result == 0 ? true : false;
	}
	else
	{
		return false;
	}
}
void SoundStream::SoundStreamImpl::Pause()
{
	Mix_PauseMusic();
}
void SoundStream::SoundStreamImpl::Stop()
{
	Mix_HaltMusic();
}
bool SoundStream::SoundStreamImpl::IsPlaying()
{
	return Mix_PlayingMusic() == 0 ? false : true;
}
void SoundStream::SoundStreamImpl::SetVolume(int value)
{
	Mix_VolumeMusic(value);
}
int SoundStream::SoundStreamImpl::GetVolume()
{
	return Mix_VolumeMusic(-1);
}
