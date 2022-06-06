#include "MiniginPCH.h"
#include "Subject.h"
#include "Observer.h"

void Subject::AddObserver(const std::shared_ptr<Observer>& observer)
{
	m_Observers[m_NrOfObservers++] = observer;
}

void Subject::NotifyAll(Event event)
{
	for (size_t i = 0; i < m_NrOfObservers; i++)
	{
		if (m_Observers[i].expired()) continue;
		m_Observers[i].lock()->OnNotify(event);
	}
}
