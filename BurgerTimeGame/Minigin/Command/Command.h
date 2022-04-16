#pragma once


class Command abstract
{
public:
	explicit Command() = default;
	virtual ~Command() = default;
	virtual void Execute() = 0;
};