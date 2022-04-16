#pragma once

enum class PlayerState
{
	Walking,
	OnLadder,
	ThrowSalt,
	Dead,
	None
};

enum class Direction
{
	Left,
	Right,
	Up,
	Down,
	None
};

class PeterPepperComponent final : public BaseComponent, public Subject
{
public:
	PeterPepperComponent(const std::shared_ptr<GameObject>& pOwner) : BaseComponent::BaseComponent(pOwner), m_Lives{3} {}
	virtual ~PeterPepperComponent();
	PeterPepperComponent(const PeterPepperComponent& other) = delete;
	PeterPepperComponent(PeterPepperComponent&& other) = delete;
	PeterPepperComponent& operator=(const PeterPepperComponent& other) = delete;
	PeterPepperComponent& operator=(PeterPepperComponent&& other) = delete;

	void OnDie();
	void OnBurgerDropped();

	void SetState(PlayerState state, Direction dir);

	const uint8_t GetLives() const { return m_Lives; }
	const int GetScore() const { return m_Score; }
private:
	uint8_t m_Lives{};
	uint32_t m_Score{};
	bool m_HasWon{};

	static const int m_MovementSpeed = 100;

	static const uint32_t m_ScoreGain = 30;
	static const uint32_t m_ScoreLoss = 50;

	void Move(Direction dir);
	void Climb(Direction dir);
};



