#pragma once

class GridComponent;
class EnemyComponent;

enum class State
{
	moveHorizontal,
	moveVertical,
	idle,
	dead,
	win
};
enum class Direction
{
	left,
	right,
	up,
	down,
	none
};

class PeterPepperComponent final : public BaseComponent, public Subject
{
public:
	PeterPepperComponent(int8_t lives = 3);
	virtual ~PeterPepperComponent() override = default;;
	PeterPepperComponent(const PeterPepperComponent& other) = delete;
	PeterPepperComponent(PeterPepperComponent&& other) = delete;
	PeterPepperComponent& operator=(const PeterPepperComponent& other) = delete;
	PeterPepperComponent& operator=(PeterPepperComponent&& other) = delete;

	void OnDie();
	void OnBurgerDropped();
	void OnLevelWin();

	bool IsStunned() const { return m_IsStunned; }
	const uint8_t GetLives() const { return m_Lives; }
	const int GetScore() const { return m_Score; }

	void AddScore(int32_t toAdd) { m_Score += toAdd; NotifyAll(Event::ScoreChanged); }
	void SetState(State state, Direction dir) { m_State = state; m_Dir = dir; }
	void AddCloseEnemy(const std::shared_ptr<EnemyComponent>& pComp);
	void RemoveCloseEnemy(const std::shared_ptr<EnemyComponent>& pComp);
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

	std::weak_ptr<SpriteComponent> m_pSpriteComponent{};
	std::weak_ptr<GridComponent> m_pGrid{};
	std::vector<std::weak_ptr<EnemyComponent>> m_pCloseEnemies{};

	int8_t m_Lives{};
	int32_t m_Score{};

	bool m_IsStunned{};
	float m_MaxStunnedTime{4.f};
	float m_TimeSinceStun{};

	static const uint32_t m_ScoreGain = 50;
	static const int m_KillRadius = 30;

	bool HandleState();
	void HandleCellCollision();
	void HandleEnemyCollisions();
};


