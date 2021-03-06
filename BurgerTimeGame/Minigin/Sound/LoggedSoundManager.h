#pragma once
#include "NullSoundManager.h"

class LoggedSoundManager final : public SoundManager
{
public:
	LoggedSoundManager(std::shared_ptr<SoundManager> wrapped) : m_Wrapped{ wrapped } 
	{
		if (!m_Wrapped) m_Wrapped = std::make_shared<NullSoundManager>();
	}
	virtual ~LoggedSoundManager() override = default;
	LoggedSoundManager(const LoggedSoundManager& other) = delete;
	LoggedSoundManager(LoggedSoundManager&& other) = delete;
	LoggedSoundManager& operator=(const LoggedSoundManager& other) = delete;
	LoggedSoundManager& operator=(LoggedSoundManager&& other) = delete;

	void PlayEffect(const soundID id, const int volume, const int loops = 0, bool waitInQueue = true) override
	{
		if (waitInQueue)
			log("Play sound effect queued\n");
		else
			log("Play sound effect now\n");

		m_Wrapped->PlayEffect(id, volume, loops, waitInQueue);
	}
	void PlayStream(const soundID id, const int volume, const bool repeat = false) override 
	{
		log("Play sound stream\n");
		m_Wrapped->PlayStream(id, volume, repeat);
	}

	virtual void StopStream() override 
	{ 
		log("Stop current soundstream\n");
		m_Wrapped->StopStream();
	}
	virtual void ClearEffectQueue() override 
	{ 
		log("Clear sound effects queue\n");
		m_Wrapped->ClearEffectQueue();
	}
	virtual void ClearStreamQueue() override 
	{ 
		log("Clear sound streams Queue\n");
		m_Wrapped->ClearStreamQueue();
	}
private:
	void log(const char* message)
	{
		printf(message);
	}
	std::shared_ptr<SoundManager> m_Wrapped;
};
