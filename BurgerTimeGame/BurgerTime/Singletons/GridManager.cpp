#include "pch.h"
#include "GridManager.h"

int GridManager::PositionToIndex(const glm::vec2& pos) const
{
    int idx{};
    int ww = Renderer::GetInstance().GetWindowWidth();
    int wh = Renderer::GetInstance().GetWindowHeight();

    if (pos.x > 0.f && pos.y > 0.f && pos.x < ww && pos.y < wh)
    {
        int xIdx = static_cast<int>(pos.x / ww * m_NrOfCols);
        int yIdx = static_cast<int>(pos.y / wh * m_NrOfRows);

        idx = xIdx + (yIdx * m_NrOfCols);
    }
    return idx;
}

glm::vec2 GridManager::IndexToPosition(int index) const
{
    glm::vec2 pos{};
    int ww = Renderer::GetInstance().GetWindowWidth();
    int wh = Renderer::GetInstance().GetWindowHeight();

    if (index < m_Grid.size() && index >= 0)
    {
        int xIdx = index % m_NrOfCols;
        int yIdx = index / m_NrOfRows;

        pos.x = static_cast<float>(xIdx * ww / m_NrOfCols);
        pos.y = static_cast<float>(yIdx * wh / m_NrOfRows);
    }
    return pos;
}
