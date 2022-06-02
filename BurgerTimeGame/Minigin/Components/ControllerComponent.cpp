#include "MiniginPCH.h"
#include "ControllerComponent.h"
#include "Components/TransformComponent.h"
#include "SceneGraph/GameObject.h"

void ControllerComponent::Move(float dispX, float dispY)
{
	auto pos = m_pTransform->GetPosition();
	m_pTransform->SetPosition(pos.x + dispX, pos.y + dispY, pos.z);
}

void ControllerComponent::Initialize()
{
	m_pTransform = GetGameObject().lock()->GetTransform();
}