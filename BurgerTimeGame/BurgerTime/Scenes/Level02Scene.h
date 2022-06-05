#pragma once
#include "Components/GridComponent.h"

class Level02Scene final : public Scene
{
public:
	Level02Scene() : Scene("Level02Scene") {}
	virtual ~Level02Scene() = default;
	Level02Scene(const Level02Scene& other) = delete;
	Level02Scene(Level02Scene&& other) noexcept = delete;
	Level02Scene& operator=(const Level02Scene& other) = delete;
	Level02Scene& operator=(Level02Scene&& other) noexcept = delete;
protected:
	void Initialize() override;
	void Update() override;

	void OnSceneActivated() override;
	void OnSceneDeactivated() override;
private:
	std::weak_ptr<GameObject> m_pP1{};
	std::weak_ptr<GameObject> m_pP2{};

	std::vector<Cell> m_LvlGrid{};
	int m_Rows{}, m_Cols{};

	void LoadLevel();
	void LoadPlayers();
	void LoadHUD();
};

