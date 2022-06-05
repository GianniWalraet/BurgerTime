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

	void LoadLevel();
	void LoadPlayers();
	void LoadHUD();
};

