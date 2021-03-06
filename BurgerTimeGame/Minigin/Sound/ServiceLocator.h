#pragma once
#include "Base/Singleton.h"
#include "SoundManager.h"
#include "NullSoundManager.h"
#include "LoggedSoundManager.h"

class ServiceLocator final
{
public:
	static std::shared_ptr<SoundManager> GetSoundManager() { return s_SMInstance; }
	static void RegisterSoundManager(std::shared_ptr<SoundManager> sm)
	{ 
		if (!sm)
		{
			s_SMInstance = std::make_shared<NullSoundManager>();
		}
		else
		{
			s_SMInstance = sm;
		}
	}
private:
	static std::shared_ptr<SoundManager> s_SMInstance;
};

