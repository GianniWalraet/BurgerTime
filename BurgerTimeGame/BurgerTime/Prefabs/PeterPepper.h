#pragma once

class PeterPepper final : public GameObject
{
public:
	PeterPepper() = default;
	virtual ~PeterPepper() override = default;
	PeterPepper(const PeterPepper& other) = delete;
	PeterPepper(PeterPepper&& other) = delete;
	PeterPepper& operator=(const PeterPepper& other) = delete;
	PeterPepper& operator=(PeterPepper&& other) = delete;

protected:
	void Initialize() override;
	void Update() override;
};

