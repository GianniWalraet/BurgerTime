#include "MiniginPCH.h"
#include "ControllerComponent.h"
#include "SceneGraph/GameObject.h"

ControllerComponent::ControllerComponent(float movementSpeed)
	: m_MoveSpeed{ movementSpeed }
{
}

void ControllerComponent::Move(float dispX, float dispY)
{
	auto pos = m_pGameObject.lock()->GetTransform().GetPosition();
	m_pGameObject.lock()->GetTransform().SetPosition(pos.x + dispX, pos.y + dispY, pos.z);
}