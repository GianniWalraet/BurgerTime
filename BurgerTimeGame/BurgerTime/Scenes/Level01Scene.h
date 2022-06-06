#pragma once

class Level01Scene final : public Scene
{
public:
	Level01Scene() : Scene("Level01Scene") {}
	virtual ~Level01Scene() = default;
	Level01Scene(const Level01Scene& other) = delete;
	Level01Scene(Level01Scene&& other) noexcept = delete;
	Level01Scene& operator=(const Level01Scene& other) = delete;
	Level01Scene& operator=(Level01Scene&& other) noexcept = delete;
protected:
	void Initialize() override;
	void Update() override;

	void OnSceneActivated() override;
	void OnSceneDeactivated() override;
private:
	std::weak_ptr<GameObject> m_pP1{};
	std::weak_ptr<GameObject> m_pP2{};

	glm::vec2 m_P1SpawnPos{};
	glm::vec2 m_P2SpawnPos{};

	float m_ElapsedTimeSinceWin{};
	float m_NextLevelWaitTime{3.f};

	float m_ElapsedTimeSinceKill{};
	float m_LevelReloadWaitTime{3.f};

	void HandleWinState();
	void HandleKillState();

	void LoadLevel();
	void LoadPlayers();
	void LoadHUD();
};

