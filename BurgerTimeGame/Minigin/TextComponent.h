#pragma once
#include "TextureComponent.h"


	class Font;
	class Texture2D;

	class TextComponent final : public TextureComponent
	{
	public:
		TextComponent() = default;
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent & other) = delete;
		TextComponent(TextComponent && other) = delete;
		TextComponent& operator=(const TextComponent & other) = delete;
		TextComponent& operator=(TextComponent && other) = delete;

		void Update() override;

		void SetFont(const std::shared_ptr<Font>& font);
		void SetText(const std::string& text);
	private:
		bool m_NeedsUpdate{ true };
		std::string m_Text{};
		std::shared_ptr<Font> m_pFont{};
	};

