#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "Base/Timer.h"
#include "Singletons/ResourceManager.h"
#include "SceneGraph/GameObject.h"
#include "TextComponent.h"


void FPSComponent::Initialize()
{
	m_pText = m_pOwner.lock()->GetComponent<TextComponent>();
	assert(m_pText != nullptr);
	m_pText->SetText(std::to_string(Timer::GetInstance().GetFPS()));
}

void FPSComponent::Update()
{
	auto fps = Timer::GetInstance().GetFPS();
	if (fps != m_PreviousFPS)
	{
		m_pText->SetText(std::to_string(fps));
		m_pText->Update();
		m_PreviousFPS = fps;
	}
}