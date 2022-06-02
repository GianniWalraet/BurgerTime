#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Graphics/Texture2D.h"
#include "Base/Timer.h"
#include "Singletons/ResourceManager.h"

SpriteComponent::SpriteComponent(const std::string& assetPath, int nrOfCols, int nrOfRows, float frameSec, const SDL_Rect& srcRect)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(assetPath);
	m_Cols = nrOfCols;
	m_Rows = nrOfRows;
	m_FrameSec = frameSec;

	if (srcRect.w != 0 && srcRect.h != 0)
	{
		m_pTexture->SetSource(srcRect);
	}
}
void SpriteComponent::Update()
{
	m_AccuSec += Timer::GetInstance().GetElapsed();

	if (m_AccuSec > m_FrameSec)
	{
		++m_ActFrame %= (m_Cols * m_Rows);
		m_AccuSec -= m_FrameSec;

		m_CurrentFrame.w = GetFrameWidth();
		m_CurrentFrame.h = GetFrameHeight();
		int col{ m_ActFrame % m_Cols };
		int row{ m_ActFrame / m_Cols };
		m_CurrentFrame.x = m_pTexture->GetSource().x + (m_CurrentFrame.w * col);
		m_CurrentFrame.y = m_pTexture->GetSource().y + (m_CurrentFrame.h * row);
	}
}

void SpriteComponent::Reset(const SDL_Rect& newSrc, int rows, int cols, bool mirror)
{
	m_pTexture->SetSource(newSrc);
	m_Rows = rows;
	m_Cols = cols;
	m_IsMirrored = mirror;
}

int SpriteComponent::GetFrameWidth()
{
	return (m_pTexture->GetSource().w / m_Cols);
}

int SpriteComponent::GetFrameHeight()
{
	return (m_pTexture->GetSource().h / m_Rows);
}
