#pragma once
#include "BaseComponent.h"


class TextureComponent;
class TextComponent;

class FPSComponent final : public BaseComponent
{
public:
	FPSComponent(const std::shared_ptr<GameObject>& pOwner) : BaseComponent::BaseComponent(pOwner) {}
	virtual ~FPSComponent() = default;
	FPSComponent(const FPSComponent& other) = delete;
	FPSComponent(FPSComponent&& other) = delete;
	FPSComponent& operator=(const FPSComponent& other) = delete;
	FPSComponent& operator=(FPSComponent&& other) = delete;

	void Initialize() override;
	void Update() override;
private:
	TextComponent* m_pText{};
	uint32_t m_PreviousFPS{};
};

