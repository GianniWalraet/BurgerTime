#pragma once
#include "Base/Singleton.h"

class SoundManager;

class ServiceLocator final : public Singleton<ServiceLocator>
{
public:
	
	static SoundManager& GetSoundManager() { return *s_SMInstance; }
	static void RegisterSoundManager(std::shared_ptr<SoundManager> sm) { s_SMInstance = sm; }
private:
	friend class Singleton;
	ServiceLocator() = default;
	static std::shared_ptr<SoundManager> s_SMInstance;
};

