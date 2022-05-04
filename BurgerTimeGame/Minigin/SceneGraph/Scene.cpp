#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "Components/RenderComponent.h"

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) { ++m_IdCounter; }

Scene::~Scene() { --m_IdCounter; }

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Initialize()
{
	for (auto& object : m_Objects)
	{
		object->RootInitialize();
	}
}

void Scene::Update()
{
	for(auto& object : m_Objects)
	{
		object->RootUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		const auto& renderComp = object->GetComponent<RenderComponent>();
		if (renderComp) renderComp->Render();

		for (const auto& comp : object->GetComponentsFromChildren<RenderComponent>())
		{
			comp->Render();
		}
	}
}