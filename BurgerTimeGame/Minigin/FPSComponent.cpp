#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "Timer.h"

void FPSComponent::Update()
{
	if (m_pText)
	{
		m_pText->SetText(std::to_string(Timer::GetInstance().GetFPS()));
		m_pText->Update();
	}
}