#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "Components/RenderComponent.h"
#include "Input/InputManager.h"

std::shared_ptr<GameObject> Scene::Add(const std::shared_ptr<GameObject>& object)
{
	object->m_pParentScene = shared_from_this();
	m_Objects.emplace_back(object);
	return object;
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
uint32_t Scene::GetNumObjectsWithTag(const Tag& tag)
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
}
void Scene::RootUpdate()
{
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