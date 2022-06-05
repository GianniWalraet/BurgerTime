#pragma once
#include "TextureComponent.h"


class Font;
class Texture2D;

class TextComponent final : public BaseComponent
{
public:
	TextComponent(const std::shared_ptr<Font>& pFont, const std::string& text = "0", const glm::vec2& pivot = {0, 0}) : m_pFont{pFont}, m_Text{text}, m_Pivot{pivot} {}
	virtual ~TextComponent() = default;
	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;

	void Update() override;

	const std::shared_ptr<Texture2D>& GetTexture() const { return m_pTexture; }
	const glm::vec2& GetPivot() const { return m_Pivot; }

	void SetFont(const std::shared_ptr<Font>& font);
	void SetText(const std::string& text);
private:
	std::shared_ptr<Texture2D> m_pTexture;
	bool m_NeedsUpdate{ true };
	std::string m_Text{};
	glm::vec2 m_Pivot{};
	std::shared_ptr<Font> m_pFont{};
};

