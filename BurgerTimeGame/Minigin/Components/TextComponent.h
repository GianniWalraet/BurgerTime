#pragma once
#include "TextureComponent.h"


class Font;
class Texture2D;

class TextComponent final : public TextureComponent
{
public:
	TextComponent(const std::shared_ptr<GameObject>& pOwner, const std::shared_ptr<Font>& pFont) : TextureComponent::TextureComponent(pOwner), m_pFont{pFont} {}
	virtual ~TextComponent() = default;
	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;

	void Update() override;

	void SetFont(const std::shared_ptr<Font>& font);
	void SetText(const std::string& text);
private:
	bool m_NeedsUpdate{ true };
	std::string m_Text{"0"};
	std::shared_ptr<Font> m_pFont{};
};

