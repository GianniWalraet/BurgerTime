#pragma once
#include "BaseComponent.h"
#include <vector>

namespace dae
{
	class TextureComponent;
	class SpriteComponent;

	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent() = default;
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		void Render();

		void AddTexture(TextureComponent* tex);
		void AddSprite(SpriteComponent* sprite);
	private:
		std::vector<TextureComponent*> m_pTextures;
		std::vector<SpriteComponent*> m_pSprites;
	};
}
