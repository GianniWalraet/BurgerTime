#include "MiniginPCH.h"
#include "ServiceLocator.h"
#include "SoundManager.h"

std::shared_ptr<SoundManager> ServiceLocator::s_SMInstance{};