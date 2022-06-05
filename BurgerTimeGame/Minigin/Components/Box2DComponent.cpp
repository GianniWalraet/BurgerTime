#include "MiniginPCH.h"
#include "Box2DComponent.h"
#include "SceneGraph/GameObject.h"
#include "Singletons/CollisionManager.h"
#include "Components/TextureComponent.h"
#include "Components/SpriteComponent.h"

Box2DComponent::Box2DComponent(float w, float h, bool isTrigger)
	: m_Width{w}
	, m_Height{h}
	, m_IsTrigger{ isTrigger }
{
	if (isTrigger)
	{
		CollisionManager::GetInstance().AddCollider(this);
	}
}
Box2DComponent::~Box2DComponent()
{
	if (m_IsTrigger)
	{
		CollisionManager::GetInstance().RemoveCollider(this);
	}
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
	glm::vec2 pivot{};
	auto texComp = m_pGameObject.lock()->GetComponent<TextureComponent>();
	auto spriteComp = m_pGameObject.lock()->GetComponent<SpriteComponent>();

	if (texComp) pivot = texComp->GetPivot();
	if (spriteComp) pivot = spriteComp->GetPivot();

	return Rectf{ pos.x - m_Width * scale.x * pivot.x, pos.y - m_Height * scale.y * pivot.y, m_Width * scale.x, m_Height * scale.y };
}
