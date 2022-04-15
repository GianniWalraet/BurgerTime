#pragma once
#include "BaseComponent.h"
#include <vector>
#include <memory>


class TextureComponent;
class SpriteComponent;
class GameObject;

class RenderComponent final : public BaseComponent
{
public:
	RenderComponent(const std::shared_ptr<GameObject>& pOwner) : BaseComponent::BaseComponent(pOwner) {}
	virtual ~RenderComponent() = default;
	RenderComponent(const RenderComponent& other) = delete;
	RenderComponent(RenderComponent&& other) = delete;
	RenderComponent& operator=(const RenderComponent& other) = delete;
	RenderComponent& operator=(RenderComponent&& other) = delete;

	void Initialize() override;
	void Render();

	//void AddTexture(TextureComponent* tex);
	//void AddSprite(SpriteComponent* sprite);
private:
	TextureComponent* m_pTexture{};
	SpriteComponent* m_pSprite{};
};

