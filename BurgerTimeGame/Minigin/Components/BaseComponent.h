#pragma once


class GameObject;

class BaseComponent
{
public:
	BaseComponent(const std::shared_ptr<GameObject>& pOwner) : m_pOwner{ pOwner } {}
	virtual ~BaseComponent() = default;
	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) = delete;

	virtual void Initialize() {};
	virtual void Update() {};
protected:
	friend class GameObject;
	std::weak_ptr<GameObject> m_pOwner;
};

