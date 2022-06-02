#pragma once


class Level final : public GameObject
{
public:
	Level(const std::string& fileName);
	virtual ~Level() override = default;
	Level(const Level& other) = delete;
	Level(Level&& other) = delete;
	Level& operator=(const Level& other) = delete;
	Level& operator=(Level&& other) = delete;
protected:
	void Initialize() override;
	void Update() override;
private:
	std::string m_FileName{};
	std::vector<std::vector<SDL_Rect>> m_Grid{};
	std::shared_ptr<Texture2D> m_pLvlSprite{};
};

