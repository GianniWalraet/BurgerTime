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
	const SDL_Rect& GetFrameSrc() const { return m_SrcRectFrame; }

	const int GetDstWidth() const { return m_DstWidth; }
	const int GetDstHeight() const { return m_DstHeight; }
private:
	std::shared_ptr<Texture2D> m_pTexture{};
	SDL_Rect m_SrcRectTex{};
	SDL_Rect m_SrcRectFrame{};
	int m_DstWidth{};
	int m_DstHeight{};

	int m_Cols{};
	int m_Rows{};
	float m_FrameSec{};
	float m_AccuSec{};
	int m_ActFrame{};

	int GetFrameWidth();
	int GetFrameHeight();
};



