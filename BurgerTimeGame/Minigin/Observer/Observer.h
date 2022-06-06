#pragma once


enum class Event
{
	PlayerDied = 0,
	ScoreChanged = 1,
};

class Observer abstract
{
public:
	virtual ~Observer() = default;
	virtual void OnNotify(Event event) = 0;
};


