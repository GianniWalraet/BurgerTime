#pragma once

#include "Minigin.h"

//#include "ImGuiManager.h"
#include "Singletons/Renderer.h"
#include "Singletons/ResourceManager.h"

#include "SceneGraph/SceneManager.h"
#include "SceneGraph/Scene.h"
#include "SceneGraph/GameObject.h"
#include "SceneGraph/Transform.h"

#include "Observer/Subject.h"
#include "Observer/Observer.h"
#include "Observer/AchievementObserver.h"

#include "Input/InputManager.h"

#include "Graphics/Texture2D.h"
#include "Graphics/Font.h"

#include "Components/BaseComponent.h"
#include "Components/FPSComponent.h"
#include "Components/RenderComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/TextComponent.h"
#include "Components/TextComponent.h"
#include "Components/ControllerComponent.h"
#include "Components/Box2DComponent.h"
#include "Components/GridComponent.h"

#include "Sound/ServiceLocator.h"

#include "Command/Command.h"

#include "Base/Timer.h"
#include "Base/Singleton.h"
#include "Base/Utils.h"