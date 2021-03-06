#pragma once
#include <condition_variable>
#include <queue>

using soundID = std::string;

class SoundEffect;
class SoundStream;

class SoundManager
{
public:
	SoundManager();
	virtual ~SoundManager();
	SoundManager(const SoundManager& other) = delete;
	SoundManager(SoundManager&& other) = delete;
	SoundManager& operator=(const SoundManager& other) = delete;
	SoundManager& operator=(SoundManager&& other) = delete;

	virtual void PlayEffect(const soundID id, const int volume, const int loops = 0, bool waitInQueue = true);
	virtual void PlayStream(const soundID id, const int volume, const bool repeat = false);

	virtual void StopStream() { m_StopCurrentStream = true; }
	virtual void ClearEffectQueue() { while (m_SoundEffectQueue.size() != 0) { m_SoundEffectQueue.pop(); } }
	virtual void ClearStreamQueue() { while (m_SoundStreamQueue.size() != 0) { m_SoundStreamQueue.pop(); } }
private:
	struct EffectInfo
	{
		soundID id{};
		int volume{};
		int loops{};
	};

	struct StreamInfo
	{
		soundID id{};
		int volume{};
		bool repeat{};
	};

	static const int m_MaxQueued = 10;
	std::queue<EffectInfo> m_SoundEffectsConcurrent;
	std::queue<EffectInfo> m_SoundEffectQueue;
	std::queue<StreamInfo> m_SoundStreamQueue;

	std::condition_variable m_CvEffectQueue{}, m_CvEffectConcurrent{};
	std::condition_variable m_CvStream{};

	bool m_RunThreads{};
	bool m_StopCurrentStream{};
	std::mutex m_Mutex{};
	std::thread m_EffectQueueThread{}, m_EffectConcurrentThread{}, m_StreamThread{};

	void EffectConcurrentThread();
	void EffectQueueThread();
	void StreamQueueThread();

	std::shared_ptr<SoundEffect> LoadEffect(const soundID& id);
	std::shared_ptr<SoundStream> LoadStream(const soundID& id);
};

