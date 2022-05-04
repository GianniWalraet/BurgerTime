#include "MiniginPCH.h"
#include "ServiceLocator.h"

std::shared_ptr<SoundManager> ServiceLocator::s_SMInstance{ std::make_shared<NullSoundManager>() };