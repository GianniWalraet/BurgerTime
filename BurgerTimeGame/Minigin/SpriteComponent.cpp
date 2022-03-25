#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Texture2D.h"
#include "Timer.h"
#include "ResourceManager.h"

dae::SpriteComponent::SpriteComponent(const std::string& assetPath, int nrOfCols, int nrOfRows, float frameSec, const glm::vec4& srcRect, float w, float h)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(assetPath);
	m_Cols = nrOfCols;
	m_Rows = nrOfRows;
	m_FrameSec = frameSec;
	m_SrcRectTex = srcRect;

	m_DstWidth = w;
	m_DstHeight = h;

	const float epsilon{ 0.001f };
	if (!(srcRect.z > epsilon && srcRect.w > epsilon))
	{
		m_SrcRectTex.z = m_pTexture->GetWidth();
		m_SrcRectTex.w = m_pTexture->GetHeight();
	}

	if (!(w > epsilon && h > epsilon))
	{
		m_DstWidth = m_pTexture->GetWidth();
		m_DstHeight = m_pTexture->GetHeight();
	}
}
void dae::SpriteComponent::Update()
{
	m_AccuSec += Timer::GetInstance().GetElapsed();

	if (m_AccuSec > m_FrameSec)
	{
		++m_ActFrame %= (m_Cols * m_Rows);
		m_AccuSec -= m_FrameSec;

		m_SrcRectFrame.z = GetFrameWidth();
		m_SrcRectFrame.w = GetFrameHeight();
		int col{ m_ActFrame % m_Cols };
		int row{ m_ActFrame / m_Cols };
		m_SrcRectFrame.x = m_SrcRectTex.x + (m_SrcRectFrame.z * col);
		m_SrcRectFrame.y = m_SrcRectTex.y + (m_SrcRectFrame.w * row);
	}
}

float dae::SpriteComponent::GetFrameWidth()
{
	return (m_SrcRectTex.z / m_Cols);
}

float dae::SpriteComponent::GetFrameHeight()
{
	return (m_SrcRectTex.w / m_Rows);
}
