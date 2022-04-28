#pragma once
#include <condition_variable>

using soundID = unsigned short;

class SoundEffect;
class SoundStream;

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	void AddEffect(const soundID id, const std::string& path);
	void AddStream(const soundID id, const std::string& path);

	void LoadEffect(const soundID id);
	void LoadStream(const soundID id);

	void PlayEffect(const soundID id, const int volume, const int loops);
	void PlayStream(const soundID id, const int volume, const bool repeat);
private:
	std::unordered_map<soundID, std::shared_ptr<SoundEffect>> m_pSoundEffects{};
	std::unordered_map<soundID, std::shared_ptr<SoundStream>> m_pSoundStreams{};

	soundID m_LoadID{};
	bool m_IsEffect{};
	std::thread m_LoaderThread{};
	std::mutex m_Mutex;
	std::condition_variable m_Cv{};

	void ThreadedLoadFunc();
	bool IsValid(const soundID id, bool isEffect);
};

