#pragma once
#include "Singletons/GridManager.h"

class LevelParser final
{
public:
	static std::vector<Cell> ParseLevel(const std::string& fileName, float scale, std::string& textureFile, int& nrRows, int& nrCols);
};

