#pragma once
#include "SceneGraph/SceneManager.h"

class GameObject;
class RenderComponent;

using Tag = std::string;

class Scene : public std::enable_shared_from_this<Scene>
{
public:
	explicit Scene(const std::string& name) : m_Name{ name } {}
	virtual ~Scene() = default;
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

	std::shared_ptr<GameObject> Add(const std::shared_ptr<GameObject>& object);
	void Remove(const std::shared_ptr<GameObject>& object);

	std::shared_ptr<GameObject> FindObjectWithTag(const Tag& tag);
	std::vector<std::shared_ptr<GameObject>> FindObjectsWithTag(const Tag& tag);
	void RemoveObjectsWithTag(const Tag& tag);
	uint32_t FindNumObjectsWithTag(const Tag& tag);

	const std::string GetName() const { return m_Name; }

	void OnSceneReload() { m_MarkedForReload = true; }
protected:
	virtual void Initialize() {}
	virtual void Update() {}	

	virtual void OnSceneActivated() {}
	virtual void OnSceneDeactivated() {}

	std::string m_Name;
private:
	friend class SceneManager;

	std::vector<std::shared_ptr<GameObject>> m_pObjectsToAdd{};
	std::vector<std::shared_ptr<GameObject>> m_pObjectsToRemove{};
	std::vector<std::shared_ptr<GameObject>> m_Objects{};

	bool m_ObjectsRemoved{};
	bool m_ObjectsAdded{};
	bool m_IsInitialized{};
	bool m_MarkedForReload{};

	void RootInitialize();
	void RootUpdate();
	void RootOnSceneActivated();
	void RootOnSceneDeactivated();
	void RootOnSceneReload();
	void Render() const;
};
