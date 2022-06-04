#pragma once
#include "SceneGraph/SceneManager.h"

class GameObject;
class RenderComponent;

class Scene
{
public:
	explicit Scene(const std::string& name) : m_Name{ name } {}
	virtual ~Scene() = default;
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

	void Add(const std::shared_ptr<GameObject>& object);
protected:
	virtual void Initialize() {}
	virtual void Update() {}	

	virtual void OnSceneActivated() {}
	virtual void OnSceneDeactivated() {}
private:
	friend class SceneManager;

	std::string m_Name;
	std::vector<std::shared_ptr<GameObject>> m_Objects{};

	void RootInitialize();
	void RootUpdate();
	void Render() const;
};
