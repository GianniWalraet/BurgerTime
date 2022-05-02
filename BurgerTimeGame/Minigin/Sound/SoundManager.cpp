#include "MiniginPCH.h"
#include "SoundManager.h"
#include "Singletons/ResourceManager.h"
#include "Sound/SoundEffect.h"
#include "Sound/SoundStream.h"

SoundManager::SoundManager()
	: m_RunThreads{ true }
{
	m_EffectQueueThread		 =	std::thread(&SoundManager::EffectQueueThread, this);
	m_StreamThread			 =	std::thread(&SoundManager::StreamQueueThread, this);
	m_EffectConcurrentThread =	std::thread(&SoundManager::EffectConcurrentThread, this);
}

SoundManager::~SoundManager()
{
	m_RunThreads = false;
	m_CvEffectQueue.notify_one();
	m_CvStream.notify_one();
	m_CvEffectConcurrent.notify_one();

	m_EffectQueueThread.join();
	m_StreamThread.join();
	m_EffectConcurrentThread.join();
}

std::shared_ptr<SoundEffect> SoundManager::LoadEffect(const soundID& id)
{
	return ResourceManager::GetInstance().LoadSoundEffect(id);
}
std::shared_ptr<SoundStream> SoundManager::LoadStream(const soundID& id)
{
	return ResourceManager::GetInstance().LoadSoundStream(id);
}

void SoundManager::PlayEffect(const soundID id, const int volume, const int loops, bool waitInQueue)
{
	std::unique_lock<std::mutex> lk(m_Mutex);
	EffectInfo info{ id, volume, loops };
	if (waitInQueue)
	{
		m_SoundEffectQueue.push_back(info);
		assert(m_SoundEffectQueue.size() < m_MaxQueued);
		m_CvEffectQueue.notify_one();
	}
	else
	{
		m_SoundEffectsConcurrent.push_back(info);
		assert(m_SoundEffectQueue.size() < m_MaxQueued);
		m_CvEffectConcurrent.notify_all();
	}
}
void SoundManager::PlayStream(const soundID id, const int volume, const bool repeat)
{
	std::unique_lock<std::mutex> lk(m_Mutex);
	StreamInfo info{ id, volume, repeat };
	m_SoundStreamQueue.push_back(info);
	m_CvStream.notify_one();
}

void SoundManager::EffectConcurrentThread()
{
	std::vector<std::shared_ptr<SoundEffect>> sounds{};
	std::unique_lock<std::mutex> lk(m_Mutex);
	while (m_RunThreads)
	{
		m_CvEffectConcurrent.wait(lk);

		// delete sounds that have finished playing
		auto it = sounds.begin();
		while (it != sounds.end())
		{
			if (!it->get()->IsPlaying()) { it = sounds.erase(it); }
			else { ++it; }
		}

		// Load and play all added soundeffects concurrently
		while (!m_SoundEffectsConcurrent.empty())
		{
			auto soundInfo = m_SoundEffectsConcurrent.front();
			m_SoundEffectsConcurrent.pop_front();

			lk.unlock();
			auto sound = LoadEffect(soundInfo.id);
			sound->Load();
			sound->SetVolume(soundInfo.volume);
			sound->Play(soundInfo.loops);
			sounds.push_back(std::move(sound));
			lk.lock();
		}
	}
}

void SoundManager::EffectQueueThread()
{
	std::shared_ptr<SoundEffect> sound{};
	std::unique_lock<std::mutex> lk(m_Mutex);
	while (m_RunThreads)
	{
		m_CvEffectQueue.wait(lk);

		while (!m_SoundEffectQueue.empty())
		{
			
			auto soundInfo = m_SoundEffectQueue.front();
			m_SoundEffectQueue.pop_front();

			lk.unlock();
			sound = LoadEffect(soundInfo.id);
			sound->Load();
			sound->SetVolume(soundInfo.volume);
			sound->Play(soundInfo.loops);

			while (sound->IsPlaying() && m_RunThreads) { Sleep(16); }
			lk.lock();
		}
	}
}

void SoundManager::StreamQueueThread()
{
	std::shared_ptr<SoundStream> sound{};
	std::unique_lock<std::mutex> lk(m_Mutex);
	while (m_RunThreads)
	{
		m_CvStream.wait(lk);

		while (!m_SoundStreamQueue.empty())
		{
			auto soundInfo = m_SoundStreamQueue.front();
			m_SoundStreamQueue.pop_front();

			lk.unlock();
			sound = LoadStream(soundInfo.id);
			sound->Load();
			sound->SetVolume(soundInfo.volume);
			auto result = sound->Play(soundInfo.repeat);

			if (!result) std::cout << "Failed to play sound " + soundInfo.id << '\n';

			while (sound->IsPlaying() && m_RunThreads) 
			{ 
				Sleep(16);
				if (m_StopCurrentStream) 
				{
					sound->Stop();
					m_StopCurrentStream = false;
				}
			}
			lk.lock();
		}
	}
}
