#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;

	class TextureComponent : public BaseComponent
	{
	public:
		TextureComponent() = default;
		TextureComponent(const std::string& filename, const glm::vec4& srcRect = { 0,0,0,0 }, float w = 0.f, float h = 0.f);
		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		const std::shared_ptr<Texture2D>& GetTexture() const { return m_pTexture; };

		const bool HasCustomSource() const { return m_HasCustomSource; }
		const bool HasCustomSize() const { return m_HasCustomSize; }

		const glm::vec4& GetSrcRect() const { return m_SrcRect; }
		const float GetWidth() const { return m_Width; }
		const float GetHeight() const { return m_Height; }
	protected:
		std::shared_ptr<Texture2D> m_pTexture;
		float m_Width{};
		float m_Height{};
	private:
		glm::vec4 m_SrcRect{};
		bool m_HasCustomSource{};
		bool m_HasCustomSize{};
	};
}

