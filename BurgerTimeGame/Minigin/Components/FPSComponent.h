#pragma once
#include "BaseComponent.h"


class TextureComponent;
class TextComponent;

class FPSComponent final : public BaseComponent
{
public:
	FPSComponent() = default;
	virtual ~FPSComponent() = default;
	FPSComponent(const FPSComponent& other) = delete;
	FPSComponent(FPSComponent&& other) = delete;
	FPSComponent& operator=(const FPSComponent& other) = delete;
	FPSComponent& operator=(FPSComponent&& other) = delete;

	void Initialize() override;
	void Update() override;
private:
	std::weak_ptr<TextComponent> m_pText{};
	uint32_t m_PreviousFPS{};
};

