#include "MiniginPCH.h"
#include "SoundManager.h"
#include "Singletons/ResourceManager.h"
#include "Sound/SoundEffect.h"
#include "Sound/SoundStream.h"

SoundManager::SoundManager()
	: m_LoaderThread{ &SoundManager::ThreadedLoadFunc, this }
{
	
}

SoundManager::~SoundManager()
{
	m_LoaderThread.join();
}

void SoundManager::AddEffect(const soundID id, const std::string& path)
{
	if (m_pSoundEffects.find(id) == m_pSoundEffects.end())
	{
		m_pSoundEffects[id] = ResourceManager::GetInstance().LoadSoundEffect(path);
	}
	else
	{
		std::string errorMsg = "SoundManager: Failed to add new effect with id " + std::to_string(id) + "\nid already exists\n";
		std::cerr << errorMsg;
	}
}
void SoundManager::AddStream(const soundID id, const std::string& path)
{
	if (m_pSoundStreams.find(id) == m_pSoundStreams.end())
	{
		m_pSoundStreams[id] = ResourceManager::GetInstance().LoadSoundStream(path);
	}
	else
	{
		std::string errorMsg = "SoundManager: Failed to add new stream with id " + std::to_string(id) + "\nid already exists\n";
		std::cerr << errorMsg;
	}
}

void SoundManager::LoadEffect(const soundID id)
{
	m_LoadID = id;
	m_IsEffect = true;
	m_Cv.notify_all();
	
}
void SoundManager::LoadStream(const soundID id)
{
	m_LoadID = id;
	m_IsEffect = false;
	m_Cv.notify_all();
}

void SoundManager::PlayEffect(const soundID id, const int volume, const int loops)
{
	if (IsValid(id, true))
	{
		m_pSoundEffects[id]->SetVolume(volume);
		m_pSoundEffects[id]->Play(loops);
	}
}
void SoundManager::PlayStream(const soundID id, const int volume, const bool repeat)
{
	if (IsValid(id, false))
	{
		m_pSoundStreams[id]->SetVolume(volume);
		m_pSoundStreams[id]->Play(repeat);
	}
}

void SoundManager::ThreadedLoadFunc()
{
	while(true)
	{
		std::unique_lock<std::mutex> lk(m_Mutex);
		m_Cv.wait(lk);

		if (m_IsEffect)
		{
			if (IsValid(m_LoadID, m_IsEffect))
				m_pSoundEffects[m_LoadID]->Load();
		}
		else
		{
			if (IsValid(m_LoadID, m_IsEffect))
				m_pSoundStreams[m_LoadID]->Load();
		}
	}
}

bool SoundManager::IsValid(const soundID id, bool isEffect)
{
	bool isValid = false;
	if (isEffect) { if (m_pSoundEffects.find(id) != m_pSoundEffects.end()) isValid = true; }
	else { if (m_pSoundStreams.find(id) != m_pSoundStreams.end()) isValid = true; }

	if (!isValid)
	{
		std::string errorMsg = "SoundManager: Stream with id " + std::to_string(id) + " doesn't exist\n";
		std::cerr << errorMsg;
	}

	return isValid;
}
