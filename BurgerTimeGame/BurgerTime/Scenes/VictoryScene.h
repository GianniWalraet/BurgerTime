#pragma once
class VictoryScene final : public Scene
{
public:
	VictoryScene() : Scene("VictoryScene") {}
	virtual ~VictoryScene() = default;
	VictoryScene(const VictoryScene& other) = delete;
	VictoryScene(VictoryScene&& other) noexcept = delete;
	VictoryScene& operator=(const VictoryScene& other) = delete;
	VictoryScene& operator=(VictoryScene&& other) noexcept = delete;
protected:
	void Initialize() override;

	void OnSceneActivated() override;
private:
	std::weak_ptr<TextComponent> m_pHighScoreTxt{};
};

