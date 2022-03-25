#pragma once
#include <vector>
#include "TransformComponent.h"

namespace dae
{
	class Texture2D;
	class BaseComponent;

	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:
		GameObject(const glm::vec3& position = { 0,0,0 }) { m_WorldTransform.SetPosition(position.x, position.y, position.z); }
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();

		template <typename T> T* AddComponent()
		{
			if (!std::is_default_constructible<T>()) return nullptr;
			auto co = new T();
			m_pComponents.push_back(co);
			co->SetOwner(shared_from_this());
			return co;
		}
		template <typename T> T* AddComponent(T* comp)
		{
			m_pComponents.push_back(comp);
			comp->SetOwner(shared_from_this());
			return comp;
		}
		template <typename T> T* GetComponent() const
		{
			for (const auto& comp : m_pComponents)
			{
				if (dynamic_cast<T*>(comp) != nullptr)
				{
					return dynamic_cast<T*>(comp);
				}
			}
			return nullptr;
		}
		template <typename T> T* GetComponentFromChildren() const
		{
			for (const auto& child : m_pChildren)
			{
				auto comp = child->GetComponent<T>();
				if (comp) return comp;
			}
			return nullptr;
		}
		template <typename T> std::vector<T*> GetComponentsFromChildren() const
		{
			std::vector<T*> comps{};
			for (const auto& child : m_pChildren)
			{
				if (child->GetChildCount() > 0)
				{
					const std::vector<T*> subComps = child->GetComponentsFromChildren<T>();
					comps.insert(comps.end(), subComps.begin(), subComps.end());
				}
				auto comp = child->GetComponent<T>();
				if (comp) comps.push_back(comp);
			}
			return comps;
		}

		template <typename T> void RemoveComponent()
		{
			for (size_t i = 0; i < m_pComponents.size(); i++)
			{
				if (dynamic_cast<T*>(m_pComponents[i]) != nullptr)
				{
					m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), m_pComponents[i]), m_pComponents.end());
				}
			}
		}

		void SetParent(const std::shared_ptr<GameObject>& parent);
		std::shared_ptr<GameObject> GetParent() const;

		size_t GetChildCount() const;
		const std::shared_ptr<GameObject>& GetChildAt(size_t index) const {return m_pChildren.at(index); }
		const std::vector<std::shared_ptr<GameObject>>& GetChildren() const { return m_pChildren; }
		void RemoveChildAt(size_t index);
		void AddChild(const std::shared_ptr<GameObject>& obj);
		void RemoveChild(const std::shared_ptr<GameObject>& obj);

		void SetPosition(const glm::vec3& pos) { m_WorldTransform.SetPosition(pos.x, pos.y, pos.z); }
		const glm::vec3& GetPosition() const { return m_WorldTransform.GetPosition(); }
	private:
		TransformComponent m_WorldTransform{};
		TransformComponent m_LocalTransform{};

		std::vector<BaseComponent*> m_pComponents{};

		std::vector<std::shared_ptr<GameObject>> m_pChildren{};
		std::weak_ptr<GameObject> m_pParent{};
	};
}