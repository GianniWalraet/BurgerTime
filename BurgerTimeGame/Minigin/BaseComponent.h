#pragma once

namespace dae
{
	class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent() = default;
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Update() {};
	protected:
		std::weak_ptr<GameObject> m_pOwner;
	private:
		friend class GameObject;
		void SetOwner(const std::shared_ptr<GameObject>& owner) { m_pOwner = owner; }
	};
}
