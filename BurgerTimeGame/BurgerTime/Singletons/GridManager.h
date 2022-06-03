#pragma once

struct Cell
{
	SDL_Rect boundingbox;
	bool isVoid;
};

class GridManager : public Singleton<GridManager>
{
public:
	virtual ~GridManager() override = default;
	GridManager(const GridManager& other) = delete;
	GridManager(GridManager&& other) = delete;
	GridManager& operator=(const GridManager& other) = delete;
	GridManager& operator=(GridManager&& other) = delete;

	void SetGrid(const std::vector<Cell>& grid, int nrRows, int nrCols)
	{
		m_Grid = grid;
		m_NrOfRows = nrRows;
		m_NrOfCols = nrCols;
	}

	const Cell& GetCell(const glm::vec2& pos) const { return m_Grid[PositionToIndex(pos)]; }
private:
	friend class Singleton;
	GridManager() = default;

	int m_NrOfCols{}, m_NrOfRows{};
	std::vector<Cell> m_Grid{};

	int PositionToIndex(const glm::vec2& pos) const;
	glm::vec2 IndexToPosition(int index) const;
};

