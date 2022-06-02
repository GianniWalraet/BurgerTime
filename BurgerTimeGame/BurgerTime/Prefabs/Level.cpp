#include "pch.h"
#include "Level.h"
#include "LevelParser/LevelParser.h"

Level::Level(const std::string& fileName)
	: m_FileName{ fileName }
{

}

void Level::Initialize()
{
	m_pLvlSprite = ResourceManager::GetInstance().LoadTexture("LevelSprite.png");
	m_Grid = LevelParser::ParseFile(m_FileName);

	for (int i = 0; i < m_Grid.size(); i++)
	{
		for (int j = 0; j < m_Grid[i].size(); j++)
		{
			auto c = AddChild(std::make_shared<GameObject>());
			auto scale = c->GetTransform()->GetScale();
			const auto& src = m_Grid[i][j];
			c->GetTransform()->SetPosition(static_cast<float>(src.w * j * scale.x), static_cast<float>(src.h * i * scale.y), 0.f);
			c->AddComponent<TextureComponent>("LevelSprite.png", false, src);
			c->AddComponent<RenderComponent>();
		}
	}
}

void Level::Update()
{

}
