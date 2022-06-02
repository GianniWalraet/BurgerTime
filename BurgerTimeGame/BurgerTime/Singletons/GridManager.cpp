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
