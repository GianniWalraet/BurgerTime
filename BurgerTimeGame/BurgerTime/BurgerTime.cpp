#include "pch.h"
#include "BurgerTime.h"

// Prefab includes
#include "Prefabs/PeterPepper.h"

// Other
#include "LevelParser/LevelParser.h"
#include "Singletons/GridManager.h"

void BurgerTime::LoadGame() const
{
#ifdef _DEBUG
	ServiceLocator::RegisterSoundManager(std::make_shared<SoundManager>());
	ServiceLocator::RegisterSoundManager(std::make_shared<LoggedSoundManager>(ServiceLocator::GetSoundManager()));
#else
	ServiceLocator::RegisterSoundManager(std::make_shared<SoundManager>());

#endif

	PrintGameInfo();

	auto& scene = SceneManager::GetInstance().CreateScene("Level01");

	// level
	{
		auto& gridManager = GridManager::GetInstance();
		auto lvlSprite = ResourceManager::GetInstance().LoadTexture("LevelSprite.png");
		auto grid = LevelParser::ParseFile("../Data/Levels/Level01.txt");

		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[i].size(); j++)
			{
				auto c = std::make_shared<GameObject>();
				c->GetTransform()->SetScale(4.f);
				auto scale = c->GetTransform()->GetScale();
				const auto& data = grid[i][j];

				int w = static_cast<int>(data.first.w * scale.x);
				int h = static_cast<int>(data.first.h * scale.y);
				int xPos = w * j;
				int yPos = h * i;

				c->GetTransform()->SetPosition(static_cast<float>(xPos), static_cast<float>(yPos), 0.f);
				c->AddComponent<TextureComponent>("LevelSprite.png", glm::vec2{ 0, 0 }, false, data.first);
				c->AddComponent<RenderComponent>();

				GridBox newBox{};
				newBox.boundingbox = { xPos, yPos, w, h };
				newBox.isSolid = data.second;
				gridManager.AddBox(newBox);

				scene.Add(c);
			}
		}
	}

	// FPS Counter
	{
		auto child = std::make_shared<GameObject>();
		child->AddComponent<TextComponent>(ResourceManager::GetInstance().LoadFont("Lingua.otf", 32));
		child->AddComponent<RenderComponent>();
		child->AddComponent<FPSComponent>();
		scene.Add(child);
	}

	// Players
	{
		auto pp = std::make_shared<PeterPepper>();
		pp->GetTransform()->SetPosition(0, 100, 0);
		pp->GetTransform()->SetScale(4.f);
		scene.Add(pp);
	}

	//ServiceLocator::GetSoundManager()->PlayStream("Sounds/Start.mp3", 20, false);
	//ServiceLocator::GetSoundManager()->PlayStream("Sounds/MainTheme.mp3", 20, true);
}

void BurgerTime::PrintGameInfo() const
{
	std::cout << "BURGER TIME GAME INFO\n";

	std::cout << '\n';

	std::cout << "PLAYER CONTROLS - XBOX CONTROLLER:\n";
	std::cout << "Movement: DPAD left-right-up-down\n";
	std::cout << "Health Decrease: A\n";
	std::cout << "Score Increase: X\n";

	std::cout << '\n';

	std::cout << "PLAYER CONTROLS - KEYBOARD:\n";
	std::cout << "PLAYER 1:\n";
	std::cout << "Movement: W(up), A(left), S(down), D(right)\n";
	std::cout << "Health Decrease: J\n";
	std::cout << "Score Increase: K\n";
	std::cout << "PLAYER 2:\n";
	std::cout << "Movement: ARROW KEYS\n";
	std::cout << "Health Decrease: L\n";
	std::cout << "Score Increase: M\n";

	std::cout << '\n';

	std::cout << "Losing Health will add a sound to the queue\nGaining Score will play a sound over other other sounds\n";
	std::cout << "\nADDITIONAL INFO: Once you reach 0 lives, gaining score or losing health will not be possible anymore,\nso no sounds will play either\n";
}