#pragma once
struct SDL_Texture;

	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	class Texture2D
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		explicit Texture2D(SDL_Texture* texture);
		~Texture2D();

		Texture2D(const Texture2D&) = delete;
		Texture2D(Texture2D&&) = delete;
		Texture2D& operator= (const Texture2D&) = delete;
		Texture2D& operator= (const Texture2D&&) = delete;

		const float GetWidth() const { return m_Width; }
		const float GetHeight() const { return m_Height; }
	private:
		SDL_Texture* m_Texture{};
		float m_Width{};
		float m_Height{};
	};

