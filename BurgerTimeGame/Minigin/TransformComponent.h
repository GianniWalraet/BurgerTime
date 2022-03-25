#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TransformComponent final : BaseComponent
	{
	public:
		TransformComponent() = default;
		virtual ~TransformComponent() = default;

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
	private:
		glm::vec3 m_Position{};
	};
}
