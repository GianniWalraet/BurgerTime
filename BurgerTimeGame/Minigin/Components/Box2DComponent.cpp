#include "MiniginPCH.h"
#include "Box2DComponent.h"
#include "SceneGraph/GameObject.h"
#include "Singletons/CollisionManager.h"

Box2DComponent::Box2DComponent(float w, float h)
	: m_Width{w}
	, m_Height{h}
{
	CollisionManager::GetInstance().AddCollider(this);
}
Box2DComponent::~Box2DComponent()
{
	CollisionManager::GetInstance().RemoveCollider(this);
}

void Box2DComponent::SetOnOverlapCallback(CollisionCallback callback)
{
	m_Callback = callback;
}

void Box2DComponent::OnOverlap(std::shared_ptr<GameObject> pTrigger, std::shared_ptr<GameObject> pOther, CollisionType type)
{
	if (m_Callback)
		m_Callback(pTrigger, pOther, type);
}

Rectf Box2DComponent::GetCollider() const
{
	auto& pos = m_pGameObject.lock()->GetTransform().GetPosition();
	auto& scale = m_pGameObject.lock()->GetTransform().GetScale();
	return Rectf{ pos.x, pos.y, m_Width * scale.x, m_Height * scale.y };
}
