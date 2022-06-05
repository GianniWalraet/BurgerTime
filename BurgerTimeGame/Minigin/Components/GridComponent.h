#pragma once
#include "BaseComponent.h"

struct Cell
{
	SDL_Rect boundingbox;
	bool isVoid;
	bool isBurgerPlatform;
	bool isPlate;
	bool isTriggered;
	bool hasBurger;

	std::weak_ptr<GameObject> pActor;
};

class GridComponent final : public BaseComponent
{
public:
	GridComponent(const std::vector<Cell>& cells, int nrRows, int nrCols);
	virtual ~GridComponent() = default;
	GridComponent(const GridComponent& other) = delete;
	GridComponent(GridComponent&& other) = delete;
	GridComponent& operator=(const GridComponent& other) = delete;
	GridComponent& operator=(GridComponent&& other) = delete;

	Cell& GetCell(const glm::vec2& pos) { return m_Grid[PositionToIndex(pos)]; }
	Cell& GetCell(int idx) { return m_Grid[idx % m_Grid.size()]; }

	int PositionToIndex(const glm::vec2& pos) const;
	glm::vec2 IndexToPosition(int index) const;

	int GetNrRows() const { return m_NrOfRows; }
	int GetNrCols() const { return m_NrOfCols; }

	int IndexToRow(int idx);
	int IndexToCol(int idx);
protected:
	void Update() override;
private:
	std::vector<Cell> m_Grid{};
	int m_NrOfCols{}, m_NrOfRows{};
};

