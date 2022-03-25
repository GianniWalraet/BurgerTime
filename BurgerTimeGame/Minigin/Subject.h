#pragma once
#define MAX_OBSERVERS 5

namespace dae
{
	enum class Event;
	class GameObject;
	class Observer;

	class Subject
	{
	public:
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
	protected:
		virtual void NotifyAll(Event event);
	private:
		Observer* m_Observers[MAX_OBSERVERS]{};
		size_t m_NrOfObservers{};
	};
}


