#pragma once
#include "TextureComponent.h"


class Font;
class Texture2D;

class TextComponent final : public BaseComponent
{
public:
	TextComponent(const std::shared_ptr<Font>& pFont) : m_pFont{pFont} {}
	virtual ~TextComponent() = default;
	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;

	void Update() override;

	const std::shared_ptr<Texture2D>& GetTexture() const { return m_pTexture; }

	void SetFont(const std::shared_ptr<Font>& font);
	void SetText(const std::string& text);
private:
	std::shared_ptr<Texture2D> m_pTexture;
	bool m_NeedsUpdate{ true };
	std::string m_Text{"0"};
	std::shared_ptr<Font> m_pFont{};
};

