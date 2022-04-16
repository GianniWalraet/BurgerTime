#pragma once


class Command abstract
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};