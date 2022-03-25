#pragma once
#include "PeterPepperComponent.h"

namespace dae
{
	class Command
	{
	public:
		explicit Command(PeterPepperComponent* actor) : m_pActor(actor) {}
		virtual ~Command() = default;
		virtual void Execute() = 0;
	protected:
		PeterPepperComponent* GetActor() const { return m_pActor; }
	private:
		PeterPepperComponent* m_pActor;
	};

	class KillCommand final : public Command
	{
	public:
		explicit KillCommand(PeterPepperComponent* actor) : Command(actor) {}
		void Execute() override
		{
			GetActor()->OnDie();
		}
	};

	class ScoreCommand final : public Command
	{
	public:
		explicit ScoreCommand(PeterPepperComponent* actor) : Command(actor) {}
		void Execute() override
		{
			GetActor()->OnBurgerDropped();
		}
	};
}
