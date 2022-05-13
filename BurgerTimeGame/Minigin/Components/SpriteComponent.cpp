#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Graphics/Texture2D.h"
#include "Base/Timer.h"
#include "Singletons/ResourceManager.h"

SpriteComponent::SpriteComponent(const std::shared_ptr<GameObject>& pOwner, const std::string& assetPath, int nrOfCols, int nrOfRows, float frameSec, const SDL_Rect& srcRect, int w, int h)
	: BaseComponent::BaseComponent(pOwner)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(assetPath);
	m_Cols = nrOfCols;
	m_Rows = nrOfRows;
	m_FrameSec = frameSec;
	m_SrcRectTex = srcRect;

	m_DstWidth = w;
	m_DstHeight = h;

	const float epsilon{ 0.001f };
	if (!(srcRect.w > 0 && srcRect.h > 0))
	{
		m_SrcRectTex.w = m_pTexture->GetWidth();
		m_SrcRectTex.h = m_pTexture->GetHeight();
	}

	if (!(w > epsilon && h > epsilon))
	{
		m_DstWidth = m_pTexture->GetWidth();
		m_DstHeight = m_pTexture->GetHeight();
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
		m_CurrentFrame.x = m_SrcRectTex.x + (m_CurrentFrame.w * col);
		m_CurrentFrame.y = m_SrcRectTex.y + (m_CurrentFrame.h * row);
	}
}

int SpriteComponent::GetFrameWidth()
{
	return (m_SrcRectTex.w / m_Cols);
}

int SpriteComponent::GetFrameHeight()
{
	return (m_SrcRectTex.h / m_Rows);
}
