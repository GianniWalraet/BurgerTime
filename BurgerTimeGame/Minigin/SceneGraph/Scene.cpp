#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "Components/RenderComponent.h"

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) { ++m_IdCounter; }

void Scene::SortRenderObjects()
{
	for (const auto& object : m_Objects)
	{
		const auto& renderComp = object->GetComponent<RenderComponent>();
		if (renderComp) m_pRenderObjs.emplace_back(renderComp);

		for (const auto& comp : object->GetComponentsFromChildren<RenderComponent>())
		{
			m_pRenderObjs.emplace_back(comp);
		}
	}

	std::sort(m_pRenderObjs.begin(), m_pRenderObjs.end(), [](RenderComponent* l, RenderComponent* r)
		{
			auto posl = l->GetOwner().lock()->GetTransform()->GetPosition();
			auto posr = r->GetOwner().lock()->GetTransform()->GetPosition();

			return posl.z < posr.z;
		});
}

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

	SortRenderObjects();
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
	for (const auto& renderObj : m_pRenderObjs)
	{
		renderObj->Render();
	}
}