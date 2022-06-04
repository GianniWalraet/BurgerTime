#pragma once

	class Transform final
	{
	public:
		Transform() = default;
		virtual ~Transform() = default;

		void SetPosition(float x, float y, float z) { SetPosition({ x, y, z }); }
		void SetPosition(const glm::vec3& position) { m_Position = position; }

		void SetScale(float scale) { SetScale({ scale, scale }); }
		void SetScale(const glm::vec2& scale) { m_Scale = scale; }

		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec2& GetScale() const { return m_Scale; }
	private:
		glm::vec3 m_Position{};
		glm::vec2 m_Scale{ 1.f, 1.f };
	};

