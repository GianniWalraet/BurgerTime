#pragma once
#include "BaseComponent.h"

class Texture2D;

class SpriteComponent : public BaseComponent
{
public:
	SpriteComponent(const std::shared_ptr<GameObject>& pOwner) : BaseComponent::BaseComponent(pOwner) {}
	SpriteComponent(const std::shared_ptr<GameObject>& pOwner, const std::string& assetPath, int nrOfRows, int nrOfCols, float frameSec, const SDL_Rect& srcRect = { 0,0,0,0 }, int w = 0, int h = 0);
	virtual ~SpriteComponent() = default;
	SpriteComponent(const SpriteComponent& other) = delete;
	SpriteComponent(SpriteComponent&& other) = delete;
	SpriteComponent& operator=(const SpriteComponent& other) = delete;
	SpriteComponent& operator=(SpriteComponent&& other) = delete;

	void Update() override;

	const std::shared_ptr<Texture2D>& GetTexture() const { return m_pTexture; }
	const SDL_Rect& GetCurrentFrame() const { return m_CurrentFrame; }

	const int GetDstWidth() const { return m_DstWidth; }
	const int GetDstHeight() const { return m_DstHeight; }
	const bool GetIsMirrored() const { return m_IsMirrored; }

	void SetSource(const SDL_Rect& newSrc) { m_SrcRectTex = newSrc; }
	void SetMirrored(bool isMirrored) { m_IsMirrored = isMirrored; }
private:
	std::shared_ptr<Texture2D> m_pTexture{};
	SDL_Rect m_SrcRectTex{};
	SDL_Rect m_CurrentFrame{};
	int m_DstWidth{};
	int m_DstHeight{};

	int m_Cols{};
	int m_Rows{};
	float m_FrameSec{};
	float m_AccuSec{};
	int m_ActFrame{};

	bool m_IsMirrored{ false };

	int GetFrameWidth();
	int GetFrameHeight();
};



