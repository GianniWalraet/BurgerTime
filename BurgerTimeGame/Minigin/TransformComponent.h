#pragma once
#include "BaseComponent.h"

	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent(const std::shared_ptr<GameObject>& pOwner) : BaseComponent::BaseComponent(pOwner) {}
		virtual ~TransformComponent() = default;

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
	private:
		glm::vec3 m_Position{};
	};

