#pragma once

struct GridBox
{
	SDL_Rect boundingbox;
	bool isSolid;
};

class GridManager : public Singleton<GridManager>
{
public:
	virtual ~GridManager() override = default;
	GridManager(const GridManager& other) = delete;
	GridManager(GridManager&& other) = delete;
	GridManager& operator=(const GridManager& other) = delete;
	GridManager& operator=(GridManager&& other) = delete;

	GridBox GetBox(const glm::vec2& pos) const { return m_Grid[PositionToIndex(pos)]; }
	void AddBox(const GridBox& newBox) { m_Grid.emplace_back(newBox); }

private:
	friend class Singleton;
	GridManager() = default;

	int m_NrOfCols{ 26 };
	int m_NrOfRows{ 26 };
	std::vector<GridBox> m_Grid{};

	int PositionToIndex(const glm::vec2& pos) const;
};

