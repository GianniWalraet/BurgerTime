#pragma once
#include "BaseComponent.h"

	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent() = default;
		virtual ~TransformComponent() = default;

		void SetPosition(float x, float y, float z) { SetPosition({ x, y, z }); }
		void SetPosition(const glm::vec3& position) { m_Position = position; }

		void SetScale(float scale) { SetScale({ scale, scale }); }
		void SetScale(const glm::vec2& scale) { m_Scale = scale; }

		const glm::mat4x4& GetWorld() { return m_World; }
		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec2& GetScale() const { return m_Scale; }
	private:
		bool m_UpdatePos{};

		glm::vec3 m_Position{};
		glm::vec2 m_Scale{ 1.f, 1.f };
		glm::mat4x4 m_World{1.f};
	};

