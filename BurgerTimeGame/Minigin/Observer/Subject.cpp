#include "MiniginPCH.h"
#include "Subject.h"
#include "Observer.h"

void Subject::AddObserver(Observer* observer)
{
	m_Observers[m_NrOfObservers++] = observer;
}
void Subject::RemoveObserver(Observer* observer)
{
	Observer* temp[MAX_OBSERVERS]{};
	int curIdx = 0;
	for (size_t i = 0; i < m_NrOfObservers; i++)
	{
		if (m_Observers[i] != observer)
		{
			temp[curIdx] = m_Observers[curIdx];
			++curIdx;
		}
	}

	memmove(m_Observers, temp, sizeof(m_Observers));
}

void Subject::NotifyAll(Event event)
{
	for (size_t i = 0; i < m_NrOfObservers; i++)
	{
		m_Observers[i]->Notify(event);
	}
}
