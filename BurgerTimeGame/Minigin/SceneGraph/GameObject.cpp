#include "MiniginPCH.h"
#include "GameObject.h"
#include "Components/BaseComponent.h"
#include "Singletons/ResourceManager.h"
#include "Singletons/Renderer.h"

GameObject::GameObject()
{
	// Each gameobject has a transform
	m_Transform = AddComponent<TransformComponent>(new TransformComponent(std::shared_ptr<GameObject>()));
}

GameObject::~GameObject()
{
	for (size_t i = 0; i < m_pComponents.size(); i++)
	{
		delete m_pComponents[i];
		m_pComponents[i] = nullptr;
	}
}

void GameObject::RootInitialize()
{
	// set owner here since we can't pass shared_from_this in the constructor
	m_Transform->m_pOwner = shared_from_this();

	for (auto& c : m_pComponents)
	{
		c->Initialize();
	}

	Initialize();

	for (auto& c : m_pChildren)
	{
		c->RootInitialize();
	}
}

void GameObject::RootUpdate()
{
	for (auto& c : m_pComponents)
	{
		c->Update();
	}

	for (auto& c : m_pChildren)
	{
		c->RootUpdate();
	}

	Update();
}

void GameObject::SetParent(const std::shared_ptr<GameObject>& parent)
{
	if (m_pParent.lock()) m_pParent.lock()->RemoveChild(shared_from_this());
	m_pParent = parent;
	if (!m_pParent.lock()) return;
	for (size_t i = 0; i < m_pParent.lock()->GetChildCount(); i++)
	{
		if (m_pParent.lock()->GetChildAt(i) == shared_from_this())
			return;
	}
	parent->AddChild(shared_from_this());
}
std::shared_ptr<GameObject> GameObject::GetParent() const
{
	return m_pParent.lock();
}

size_t GameObject::GetChildCount() const
{
	return m_pChildren.size();
}
void GameObject::RemoveChildAt(size_t index)
{
	if (index >= m_pChildren.size()) return;
	m_pChildren[index]->SetParent(nullptr);
	m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), m_pChildren[index]), m_pChildren.end());
}
std::shared_ptr<GameObject> GameObject::AddChild(const std::shared_ptr<GameObject>& obj)
{
	// Return if child was already added
	auto child = std::find_if(m_pChildren.begin(), m_pChildren.end(), [&](std::shared_ptr<GameObject>& lhs) { return lhs == obj; });
	if (child != m_pChildren.end()) return obj;
	// Add child to children
	m_pChildren.push_back(obj);
	// If child has a parent, remove child from parent
	if (obj->GetParent()) obj->GetParent()->RemoveChild(obj);
	// Set child's new parent if not already done
	if(obj->GetParent() != shared_from_this()) obj->SetParent(shared_from_this());
	return obj;
}
void GameObject::RemoveChild(const std::shared_ptr<GameObject>& obj)
{
	auto child = std::find_if(m_pChildren.begin(), m_pChildren.end(), [&](std::shared_ptr<GameObject>& lhs) { return lhs == obj; });
	if (child == m_pChildren.end()) return;
	m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), *child), m_pChildren.end());
}
