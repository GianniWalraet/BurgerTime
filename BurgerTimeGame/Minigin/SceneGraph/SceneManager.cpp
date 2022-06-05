#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void SceneManager::Initialize()
{
	for (auto& scene : m_Scenes)
	{
		scene->RootInitialize();
	}

	m_ActiveScene = m_Scenes.front();
	m_ActiveScene->RootOnSceneActivated();
}

void SceneManager::Update()
{
	m_ActiveScene->RootUpdate();
}

void SceneManager::Render() const
{
	m_ActiveScene->Render();
}

void SceneManager::SetActiveScene(const std::string& name)
{
	for (size_t i = 0; i < m_Scenes.size(); i++)
	{
		if (m_Scenes[i]->m_Name == name)
		{
			m_ActiveScene->RootOnSceneDeactivated();
			m_ActiveScene = m_Scenes[i];
			m_ActiveScene->RootOnSceneActivated();
			break;
		}
	}
}

void SceneManager::AddScene(const std::shared_ptr<Scene>& scene)
{
	m_Scenes.push_back(scene);
}
