#pragma once
#include "TextureComponent.h"
#include "SpriteComponent.h"
#include "TextComponent.h"

class RenderComponent final : public BaseComponent
{
public:
	RenderComponent() = default;
	virtual ~RenderComponent() = default;
	RenderComponent(const RenderComponent& other) = delete;
	RenderComponent(RenderComponent&& other) = delete;
	RenderComponent& operator=(const RenderComponent& other) = delete;
	RenderComponent& operator=(RenderComponent&& other) = delete;
protected:
	void Initialize() override;
	void Render();
private:
	friend class Scene;
	TextureComponent* m_pTexture{};
	SpriteComponent* m_pSprite{};
	TextComponent* m_pText{};
};

