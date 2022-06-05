#pragma once

struct LevelData
{
	std::string backgroundFileName{};
	int nrOfRows{};
	int nrOfCols{};
	std::vector<Cell> gridCells{};
	std::vector<std::shared_ptr<GameObject>> burgers{};
	std::vector<int> playerSpawnCellIndices{};
	std::vector<int> enemySpawnCellIndices{};
};

class LevelParser final
{
public:
	static void ParseLevel(const std::string& fileName, float scale, LevelData& data);
};

