#pragma once


class GameObject;

class BaseComponent
{
public:
	BaseComponent() = default;
	virtual ~BaseComponent() = default;
	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) = delete;

	virtual void Initialize() {};
	virtual void Update() {};

	const std::weak_ptr<GameObject> GetGameObject() const { return m_pGameObject; }
protected:
	friend class GameObject;
	std::weak_ptr<GameObject> m_pGameObject;
};

