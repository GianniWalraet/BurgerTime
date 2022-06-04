#pragma once
#include "BaseComponent.h"
#include "Base/Structs.h"
#include <functional>

enum class CollisionType
{
	ENTER,
	EXIT
};

using CollisionCallback = std::function<void(std::shared_ptr<GameObject> pTrigger, std::shared_ptr<GameObject> pOther, CollisionType type)>;

class Box2DComponent : public BaseComponent
{
public:
	Box2DComponent(float w, float h, bool isTrigger);
	virtual ~Box2DComponent() override;
	Box2DComponent(const Box2DComponent& other) = delete;
	Box2DComponent(Box2DComponent&& other) = delete;
	Box2DComponent& operator=(const Box2DComponent& other) = delete;
	Box2DComponent& operator=(Box2DComponent&& other) = delete;

	void SetOnOverlapCallback(CollisionCallback callback);
	void OnOverlap(std::shared_ptr<GameObject> pTrigger, std::shared_ptr<GameObject> pOther, CollisionType type);

	Rectf GetCollider() const;
private:
	float m_Width{}, m_Height{};
	bool m_IsTrigger{};
	CollisionCallback m_Callback{};
};

