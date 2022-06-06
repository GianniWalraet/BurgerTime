#pragma once


class Level03Scene final : public Scene
{
public:
	Level03Scene() : Scene("Level03Scene") {}
	virtual ~Level03Scene() = default;
	Level03Scene(const Level03Scene& other) = delete;
	Level03Scene(Level03Scene&& other) noexcept = delete;
	Level03Scene& operator=(const Level03Scene& other) = delete;
	Level03Scene& operator=(Level03Scene&& other) noexcept = delete;
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
	float m_NextLevelWaitTime{ 3.f };

	float m_ElapsedTimeSinceKill{};
	float m_LevelReloadWaitTime{ 3.f };

	void HandleWinState();
	void HandleKillState();

	void LoadLevel();
	void LoadPlayers();
	void LoadHUD();
};


