#pragma once
#include "SceneGraph/SceneManager.h"

class GameObject;
class RenderComponent;

class Scene
{
	friend Scene& SceneManager::CreateScene(const std::string& name);
public:
	void Add(const std::shared_ptr<GameObject>& object);

	void Initialize();
	void Update();
	void Render() const;

	~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

private:
	explicit Scene(const std::string& name);

	std::string m_Name;
	std::vector <std::shared_ptr<GameObject>> m_Objects{};
	std::vector <RenderComponent*> m_pRenderObjs{};

	static unsigned int m_IdCounter;

	void SortRenderObjects();
};
