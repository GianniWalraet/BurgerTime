#include "MiniginPCH.h"
#include "SoundManager.h"
#include "Singletons/ResourceManager.h"
#include "Sound/SoundEffect.h"
#include "Sound/SoundStream.h"

SoundManager::SoundManager()
	: m_EffectQueueThread{ &SoundManager::EffectPlayerQueueThread, this }
	, m_StreamThread{ &SoundManager::StreamPlayerThread, this }
	, m_EffectConcurrentThread{ &SoundManager::EffectPlayerConcurrentThread, this }
	, m_RunThreads{ true }
{

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
		m_CvEffectQueue.notify_one();
	}
	else
	{
		m_ConcurrentEffects.push_back(info);
		m_CvEffectConcurrent.notify_all();
	}
}
void SoundManager::PlayStream(const soundID id, const int volume, const bool repeat)
{
	StreamInfo info{ id, volume, repeat };
	m_SoundStreamQueue.push_back(info);
	m_CvStream.notify_one();
}

void SoundManager::EffectPlayerConcurrentThread()
{
	std::vector<std::shared_ptr<SoundEffect>> sounds{};
	std::unique_lock<std::mutex> lk(m_Mutex);
	while (m_RunThreads)
	{
		m_CvEffectConcurrent.wait(lk);

		while (!m_ConcurrentEffects.empty())
		{
			auto soundInfo = m_ConcurrentEffects.front();
			m_ConcurrentEffects.pop_front();

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

void SoundManager::EffectPlayerQueueThread()
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

			while (sound->IsPlaying() && m_RunThreads) {}
			lk.lock();
		}
	}
}

void SoundManager::StreamPlayerThread()
{
	std::shared_ptr<SoundStream> currentSound{};
	std::unique_lock<std::mutex> lk(m_Mutex);
	while (m_RunThreads)
	{
		m_CvStream.wait(lk);

		while (!m_SoundStreamQueue.empty())
		{
			auto soundInfo = m_SoundStreamQueue.front();
			m_SoundStreamQueue.pop_front();

			lk.unlock();
			currentSound = LoadStream(soundInfo.id);
			currentSound->Load();
			currentSound->SetVolume(soundInfo.volume);
			currentSound->Play(soundInfo.repeat);

			while (currentSound->IsPlaying() && m_RunThreads) {}
			lk.lock();
		}
	}
}
