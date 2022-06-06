#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "Components/RenderComponent.h"
#include "Input/InputManager.h"

std::shared_ptr<GameObject> Scene::Add(const std::shared_ptr<GameObject>& object)
{
	object->m_pParentScene = shared_from_this();
	if (m_IsInitialized)
	{
		m_pObjectsToAdd.emplace_back(object);
		m_ObjectsAdded = true;
	}
	else
	{
		m_Objects.emplace_back(object);
	}

	return object;
}
void Scene::Remove(const std::shared_ptr<GameObject>& object)
{
	m_pObjectsToRemove.emplace_back(object);
	m_ObjectsRemoved = true;
}

std::shared_ptr<GameObject> Scene::FindObjectWithTag(const Tag& tag)
{
	for (const auto& obj : m_Objects)
	{
		if (obj->CompareTag(tag))
		{
			return obj;
		}
	}
	return nullptr;
}
std::vector<std::shared_ptr<GameObject>> Scene::FindObjectsWithTag(const Tag& tag)
{
	std::vector<std::shared_ptr<GameObject>> pObjects{};
	for (const auto& obj : m_Objects)
	{
		if (obj->CompareTag(tag))
		{
			pObjects.emplace_back(obj);
		}
	}
	return pObjects;
}
void Scene::RemoveObjectsWithTag(const Tag& tag)
{
	for (const auto& obj : m_Objects)
	{
		if (obj->CompareTag(tag))
		{
			m_pObjectsToRemove.emplace_back(obj);
		}
	}
	m_ObjectsRemoved = true;
}
uint32_t Scene::FindNumObjectsWithTag(const Tag& tag)
{
	uint32_t amount{};
	for (const auto& obj : m_Objects)
	{
		if (obj->CompareTag(tag))
			++amount;
	}

	return amount;
}

void Scene::RootInitialize()
{
	Initialize();

	for (auto& object : m_Objects)
	{
		object->RootInitialize();
	}

	m_IsInitialized = true;
}
void Scene::RootUpdate()
{
	if (m_MarkedForReload)
		RootOnSceneReload();

	if (!m_IsInitialized)
		RootInitialize();

	if (m_ObjectsAdded)
	{
		m_Objects.insert(m_Objects.end(), m_pObjectsToAdd.begin(), m_pObjectsToAdd.end());
		m_pObjectsToAdd.clear();
		m_ObjectsAdded = false;
	}

	if (m_ObjectsRemoved)
	{
		for (size_t i = 0; i < m_pObjectsToRemove.size(); i++)
		{
			m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), m_pObjectsToRemove[i]), m_Objects.end());
		}
		m_pObjectsToRemove.clear();
		m_ObjectsRemoved = false;
	}

	Update();

	for (auto& object : m_Objects)
	{
		object->RootUpdate();
	}
}
void Scene::RootOnSceneActivated()
{
	InputManager::GetInstance().SetActiveScene(m_Name);
	OnSceneActivated();
}
void Scene::RootOnSceneDeactivated()
{
	OnSceneDeactivated();
}

void Scene::RootOnSceneReload()
{
	RootOnSceneDeactivated();

	m_IsInitialized = false;
	m_ObjectsAdded = false;
	m_ObjectsRemoved = false;
	m_Objects.clear();
	m_pObjectsToAdd.clear();
	m_pObjectsToRemove.clear();
	InputManager::GetInstance().RemoveAllCommands(m_Name);

	RootInitialize();
	RootOnSceneActivated();
	m_MarkedForReload = false;
}

void Scene::Render() const
{
	for (const auto& obj : m_Objects)
	{
		if (!obj->IsEnabled()) continue;
		if (auto renderComponent = obj->GetComponent<RenderComponent>())
		{
			renderComponent->Render();
		}
	}
}