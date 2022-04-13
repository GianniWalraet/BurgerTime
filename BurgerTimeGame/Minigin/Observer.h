#pragma once



	enum class Event
	{
		PlayerDied = 0,
		BurgerDropped = 1,
	};

	class Observer abstract
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(Event event) = 0;
	};


