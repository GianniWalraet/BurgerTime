#pragma once


class DefeatScene final : public Scene
{
public:
	DefeatScene() : Scene("DefeatScene") {}
	virtual ~DefeatScene() = default;
	DefeatScene(const DefeatScene& other) = delete;
	DefeatScene(DefeatScene&& other) noexcept = delete;
	DefeatScene& operator=(const DefeatScene& other) = delete;
	DefeatScene& operator=(DefeatScene&& other) noexcept = delete;
protected:
	void Initialize() override;
};

