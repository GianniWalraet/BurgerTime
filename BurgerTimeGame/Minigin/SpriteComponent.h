#pragma once
#include "BaseComponent.h"

	class Texture2D;

	class SpriteComponent : public BaseComponent
	{
	public:
		SpriteComponent() = default;
		SpriteComponent(const std::string& assetPath, int nrOfRows, int nrOfCols, float frameSec, const glm::vec4& srcRect = {0,0,0,0}, float w = 0, float h = 0);
		virtual ~SpriteComponent() = default;
		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		void Update() override;

		const std::shared_ptr<Texture2D>& GetTexture() const { return m_pTexture; }
		const glm::vec4& GetFrameSrc() const { return m_SrcRectFrame; }

		const float GetDstWidth() const { return m_DstWidth; }
		const float GetDstHeight() const { return m_DstHeight; }
	private:
		std::shared_ptr<Texture2D> m_pTexture{};
		glm::vec4 m_SrcRectTex{};
		glm::vec4 m_SrcRectFrame{};
		float m_DstWidth{};
		float m_DstHeight{};

		int m_Cols{};
		int m_Rows{};
		float m_FrameSec{};
		float m_AccuSec{};
		int m_ActFrame{};

		float GetFrameWidth();
		float GetFrameHeight();
	};



