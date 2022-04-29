#pragma once
#include <condition_variable>

using soundID = std::string;

class SoundEffect;
class SoundStream;

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	void PlayEffect(const soundID id, const int volume, const int loops = 0, bool waitInQueue = true);
	void PlayStream(const soundID id, const int volume, const bool repeat = false);
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

	std::deque<EffectInfo> m_ConcurrentEffects{};
	std::deque<EffectInfo> m_SoundEffectQueue{};
	std::deque<StreamInfo> m_SoundStreamQueue{};

	std::condition_variable m_CvEffectQueue{}, m_CvEffectConcurrent{};
	std::condition_variable m_CvStream{};

	bool m_RunThreads{};
	std::mutex m_Mutex;
	std::thread m_EffectQueueThread{}, m_EffectConcurrentThread{}, m_StreamThread{};

	void EffectPlayerConcurrentThread();
	void EffectPlayerQueueThread();
	void StreamPlayerThread();

	std::shared_ptr<SoundEffect> LoadEffect(const soundID& id);
	std::shared_ptr<SoundStream> LoadStream(const soundID& id);
};

