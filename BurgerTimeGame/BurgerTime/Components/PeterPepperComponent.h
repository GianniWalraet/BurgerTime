#pragma once
#include "Implementations/State/PlayerStates.h"


class PeterPepperComponent final : public BaseComponent, public Subject
{
public:
	PeterPepperComponent(const std::shared_ptr<GameObject>& pOwner);
	virtual ~PeterPepperComponent();
	PeterPepperComponent(const PeterPepperComponent& other) = delete;
	PeterPepperComponent(PeterPepperComponent&& other) = delete;
	PeterPepperComponent& operator=(const PeterPepperComponent& other) = delete;
	PeterPepperComponent& operator=(PeterPepperComponent&& other) = delete;

	void OnDie();
	void OnBurgerDropped();

	template <typename T>
	void SetState()
	{
		m_StateSet = true;
		if (dynamic_cast<T*>(m_pSetState) == nullptr)
		{
			delete m_pSetState;
			m_pSetState = new T(this);
		}
	}

	const uint8_t GetLives() const { return m_Lives; }
	const int GetScore() const { return m_Score; }
protected:
	void Initialize() override;
	void Update() override;
private:
	int8_t m_Lives{};
	int32_t m_Score{};
	bool m_HasWon{};
	bool m_StateSet{};

	static const uint32_t m_ScoreGain = 30;
	static const uint32_t m_ScoreLoss = 50;

	PlayerState* m_pCurrentState{};
	PlayerState* m_pPreviousState{};

	PlayerState* m_pDefaultState{};
	PlayerState* m_pSetState{};
};



