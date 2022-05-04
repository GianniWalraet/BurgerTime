#pragma once
#include "SceneGraph/GameObject.h"

class Command abstract
{
public:
	Command(std::shared_ptr<GameObject> actor) : m_pActor{ actor } {}
	virtual ~Command() = default;
	virtual void Execute() = 0;
private:
	std::weak_ptr<GameObject> m_pActor{};
};