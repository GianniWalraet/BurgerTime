#pragma once
#include "BaseComponent.h"

class Texture2D;

class TextureComponent : public BaseComponent
{
public:
	TextureComponent(const std::shared_ptr<GameObject>& pOwner) : BaseComponent::BaseComponent(pOwner) {}
	TextureComponent(const std::shared_ptr<GameObject>& pOwner, const std::string& filename, bool mirrored = false, const SDL_Rect& srcRect = { 0,0,0,0 });
	virtual ~TextureComponent() = default;
	TextureComponent(const TextureComponent& other) = delete;
	TextureComponent(TextureComponent&& other) = delete;
	TextureComponent& operator=(const TextureComponent& other) = delete;
	TextureComponent& operator=(TextureComponent&& other) = delete;

	const std::shared_ptr<Texture2D>& GetTexture() const { return m_pTexture; };
	const bool HasCustomSource() { return m_HasCustomSource; }
	const bool IsMirrored() const { return m_IsMirrored; }
protected:
	std::shared_ptr<Texture2D> m_pTexture;
	glm::vec2 m_Scale{};
	bool m_IsMirrored{};
private:
	bool m_HasCustomSource{};
};


