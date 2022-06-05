#pragma once

class LevelParser final
{
public:
	static void ParseLevel(const std::string& fileName, float scale, std::string& textureFile, int& nrRows, int& nrCols, std::vector<Cell>& cells, std::vector<std::shared_ptr<GameObject>>& burgers);
};

