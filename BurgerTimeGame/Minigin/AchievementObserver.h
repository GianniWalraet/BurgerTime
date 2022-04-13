#pragma once
#include "Singleton.h"


	enum class EAchievements
	{
		GameWin = 0,
	};

	class AchievementObserver : public Singleton<AchievementObserver>
	{
	public:
		AchievementObserver() = default;
		~AchievementObserver() = default;
		AchievementObserver(const AchievementObserver& other) = delete;
		AchievementObserver(AchievementObserver&& other) = delete;
		AchievementObserver& operator=(const AchievementObserver& other) = delete;
		AchievementObserver& operator=(AchievementObserver&& other) = delete;

		virtual void Notify(EAchievements event);
	};


