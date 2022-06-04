#include "pch.h"
#include "LevelParser.h"
#include "Components/BurgerComponent.h"

void LevelParser::ParseLevel(const std::string& fileName, float scale, std::string& textureFile, int& nrRows, int& nrCols,
	std::vector<Cell>& cells, std::vector<std::shared_ptr<GameObject>>& burgers)
{
	std::ifstream file(fileName);
	if (!file) throw std::runtime_error("Invalid Level file!\n");

	std::string line{};

	// Get the texture of the lvl
	{
		std::getline(file, line);
		textureFile = line;
	}

	// Get the rows and cols of the lvl
	{
		std::getline(file, line);
		std::istringstream str{ line };
		str >> nrRows >> nrCols;
	}

	// Get the dimensions of 1 cell
	int cellW, cellH;
	{
		std::getline(file, line);
		std::istringstream str{ line };
		str >> cellW >> cellH;
	}

	int i{};
	while (std::getline(file, line))
	{
		for (int j = 0; j < line.size(); j++)
		{
			bool isBurgerPlatform = (line[j] == '=' || line[j] == 'n' || line[j] == 's' || line[j] == 'c' || line[j] == 't' || line[j] == 'b' || line[j] == 'v');
			cells.emplace_back(Cell{ SDL_Rect{ int(j * cellW * scale), int(i * cellH * scale),int(cellW * scale), int(cellH * scale) }, line[j] == '#', isBurgerPlatform });

			if (line[j] == '#' || line[j] == 'o' || line[j] == '=') continue;
			if (line[j - 1] != '#' && line[j - 1] != 'o') continue;

			BurgerType type{};
			switch (line[j])
			{
			case 'n':
				type = BurgerType::bunTop;
				break;
			case 's':
				type = BurgerType::salad;
				break;
			case 'c':
				type = BurgerType::cheese;
				break;
			case 't':
				type = BurgerType::tomato;
				break;
			case 'b':
				type = BurgerType::burger;
				break;
			case 'v':
				type = BurgerType::bunBottom;
				break;
			}

			int burgerPieces{ 4 };
			std::vector<Box2DComponent*> colliders{};
			for (size_t i = 0; i < burgerPieces; i++)
			{
				auto triggerBoxGO = std::make_shared<GameObject>();
				auto box2DComp = triggerBoxGO->AddComponent<Box2DComponent>(float(cellW * scale), float(cellH * scale), true);
				colliders.emplace_back(box2DComp);
			}

			auto burgerObj = std::make_shared<GameObject>();
			int currentIdx = (j + i * nrCols) - nrCols;
			burgerObj->AddComponent<BurgerComponent>(colliders);
			burgerObj->AddComponent<TextureComponent>("LevelSprite.png", glm::vec2{ 0,0 }, false, SDL_Rect{ cellW * 8, cellH * static_cast<int>(type), cellW * 4, cellH });
			burgerObj->AddComponent<RenderComponent>();




			burgerObj->GetTransform().SetPosition(float(j * cellW * scale), float(i * cellH * scale) - 32.f, 0.f);
			burgerObj->GetTransform().SetScale(scale);

			burgers.emplace_back(burgerObj);
		}
		++i;
	}
}

