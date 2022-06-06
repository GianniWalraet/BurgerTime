#pragma once
#define MAX_OBSERVERS 5


enum class Event;
class GameObject;
class Observer;

class Subject
{
public:
	void AddObserver(const std::shared_ptr<Observer>& observer);
protected:
	virtual void NotifyAll(Event event);
private:
	std::weak_ptr<Observer> m_Observers[MAX_OBSERVERS]{};
	size_t m_NrOfObservers{};
};



