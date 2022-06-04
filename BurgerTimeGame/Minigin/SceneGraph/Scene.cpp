#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "Components/RenderComponent.h"

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.emplace_back(object);
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

	for(auto& object : m_Objects)
	{
		object->RootUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& obj : m_Objects)
	{
		if (auto renderComponent = obj->GetComponent<RenderComponent>())
		{
			renderComponent->Render();
		}
	}
}