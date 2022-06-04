#pragma once
#include "Base/Singleton.h"

class Scene;

class SceneManager final : public Singleton<SceneManager>
{
public:
	void AddScene(const std::shared_ptr<Scene>& scene);

	void Initialize();
	void Update();
	void Render() const;

	void SetActiveScene(const std::string& name);
private:
	friend class Singleton<SceneManager>;
	SceneManager() = default;
	std::vector<std::shared_ptr<Scene>> m_Scenes{};

	std::shared_ptr<Scene> m_ActiveScene{};
};

