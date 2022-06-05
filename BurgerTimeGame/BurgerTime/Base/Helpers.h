#pragma once
#include "Command/PlayerCommands.h"
#include <Components/HealthDisplayComponent.h>
#include <Components/ScoreDisplayComponent.h>

enum class PlayerID
{
	PLAYERONE = 0,
	PLAYERTWO = 1
};

namespace Helpers
{
	std::shared_ptr<GameObject> CreatePlayer(const std::shared_ptr<Scene>& scene, PlayerID id);
};

