#pragma once
#include "BaseComponent.h"

class Texture2D;

class SpriteComponent : public BaseComponent
{
public:
	SpriteComponent(const std::string& assetPath, int nrOfRows, int nrOfCols, float frameSec, const glm::vec2& pivot = {0,0}, const SDL_Rect& srcRect = { 0,0,0,0 });
	virtual ~SpriteComponent() = default;
	SpriteComponent(const SpriteComponent& other) = delete;
	SpriteComponent(SpriteComponent&& other) = delete;
	SpriteComponent& operator=(const SpriteComponent& other) = delete;
	SpriteComponent& operator=(SpriteComponent&& other) = delete;

	void Update() override;

	const std::shared_ptr<Texture2D>& GetTexture() const { return m_pTexture; }
	const SDL_Rect& GetCurrentFrame() const { return m_CurrentFrame; }
	const glm::vec2& GetPivot() const { return m_Pivot; }

	const bool IsMirrored() const { return m_IsMirrored; }

	void Reset(const SDL_Rect& newSrc, int rows, int cols, bool mirror, float frameSec = 1/10.f);
private:
	std::shared_ptr<Texture2D> m_pTexture{};
	SDL_Rect m_CurrentFrame{};
	glm::vec2 m_Pivot{};

	int m_Cols{};
	int m_Rows{};
	float m_FrameSec{};
	float m_AccuSec{};
	int m_ActFrame{};

	bool m_IsMirrored{ false };

	int GetFrameWidth();
	int GetFrameHeight();
};



