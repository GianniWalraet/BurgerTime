#pragma once

enum class State
{
	moveHorizontal,
	moveVertical,
	idle,
	dead
};
enum class Direction
{
	left,
	right,
	up,
	down
};


class PeterPepperComponent final : public BaseComponent, public Subject
{
public:
	PeterPepperComponent();
	virtual ~PeterPepperComponent();
	PeterPepperComponent(const PeterPepperComponent& other) = delete;
	PeterPepperComponent(PeterPepperComponent&& other) = delete;
	PeterPepperComponent& operator=(const PeterPepperComponent& other) = delete;
	PeterPepperComponent& operator=(PeterPepperComponent&& other) = delete;

	void OnDie();
	void OnBurgerDropped();

	const uint8_t GetLives() const { return m_Lives; }
	const int GetScore() const { return m_Score; }

	void SetState(State state, Direction dir) { m_State = state; m_Dir = dir; }
protected:
	void Initialize() override;
	void Update() override;
private:
	State m_State{};
	State m_PrevState{};
	Direction m_Dir{};
	Direction m_PrevDir{};

	int m_CellIdx{};
	int m_PrevCellIdx{};

	SpriteComponent* m_pSpriteComponent{};
	int8_t m_Lives{};
	int32_t m_Score{};
	bool m_HasWon{};

	static const uint32_t m_ScoreGain = 50;
	static const uint32_t m_ScoreLoss = 50;

	bool HandleState();
};



