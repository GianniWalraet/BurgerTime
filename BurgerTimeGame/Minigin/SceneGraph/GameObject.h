#pragma once
#include <vector>
#include "SceneGraph/Transform.h"

class Texture2D;
class BaseComponent;

using Tag = std::string;

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
	GameObject() = default;
	virtual ~GameObject();
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	template <typename T, typename... Args> T* AddComponent(Args... args)
	{
		auto co = new T(std::forward<Args>(args)...);
		RootAddComponent(co);
		return co;
	}
	template <typename T> T* AddComponent(T* comp)
	{
		RootAddComponent(comp);
		return comp;
	}
	template <typename T> T* GetComponent() const
	{
		for (const auto comp : m_pComponents)
		{
			if (dynamic_cast<T*>(comp) != nullptr)
			{
				return dynamic_cast<T*>(comp);
			}
		}
		return nullptr;
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

	const Tag& GetTag() const { return m_Tag; };
	void SetTag(const Tag& newTag) { m_Tag = newTag; }

#pragma region childParentFuncs
	//template <typename T> T* GetComponentFromChildren() const
	//{
	//	for (const auto& child : m_pChildren)
	//	{
	//		auto comp = child->GetComponent<T>();
	//		if (comp) return comp;
	//	}
	//	return nullptr;
	//}
	//template <typename T> std::vector<T*> GetComponentsFromChildren() const
	//{
	//	std::vector<T*> comps{};

	//	if (GetChildCount() == 0) return comps;

	//	for (const auto& child : m_pChildren)
	//	{
	//		const auto comp = child->GetComponent<T>();
	//		const auto subComps = child->GetComponentsFromChildren<T>();
	//		if (comps.size() > 0)comps.insert(comps.end(), subComps.begin(), subComps.end());
	//		if (comp) comps.push_back(comp);
	//	}
	//	return comps;
	//}

	//void SetParent(const std::shared_ptr<GameObject>& parent);
	//std::shared_ptr<GameObject> GetParent() const;

	//size_t GetChildCount() const;
	//std::vector<std::shared_ptr<GameObject>> GetChildren() { return m_pChildren; }
	//const std::shared_ptr<GameObject>& GetChildAt(size_t index) const { return m_pChildren.at(index); }
	//void RemoveChildAt(size_t index);
	//std::shared_ptr<GameObject> AddChild(const std::shared_ptr<GameObject>& obj);
	//void RemoveChild(const std::shared_ptr<GameObject>& obj);
#pragma endregion

	Transform& GetTransform() { return m_Transform; }
protected:
	virtual void Initialize() {}
	virtual void Update() {}
private:
	friend class Scene;
	Tag m_Tag{};

	Transform m_Transform{};
	std::vector<BaseComponent*> m_pComponents{};

	//std::vector<std::shared_ptr<GameObject>> m_pChildren{};
	//std::weak_ptr<GameObject> m_pParent{};

	void RootInitialize();
	void RootUpdate();
	void RootAddComponent(BaseComponent* pComp);
};
