#pragma once
#include "Implementations/State/PlayerStates.h"


class PeterPepperComponent final : public BaseComponent, public Subject
{
public:
	PeterPepperComponent(const std::shared_ptr<GameObject>& pOwner) : BaseComponent(pOwner), m_Lives{3} {}
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
		if (dynamic_cast<T*>(m_pState) == nullptr)
		{
			if (m_pState) delete m_pState;
			m_pState = new T(m_pOwner.lock()->GetComponent<PeterPepperComponent>());
		}
	}

	const uint8_t GetLives() const { return m_Lives; }
	const int GetScore() const { return m_Score; }
private:
	int8_t m_Lives{};
	int32_t m_Score{};
	bool m_HasWon{};

	static const int m_MovementSpeed = 100;

	static const uint32_t m_ScoreGain = 30;
	static const uint32_t m_ScoreLoss = 50;

	PlayerState* m_pState{};
};



