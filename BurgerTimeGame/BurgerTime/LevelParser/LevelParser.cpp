#include "pch.h"
#include "LevelParser.h"

std::vector<Cell> LevelParser::ParseLevel(const std::string& fileName, float scale, std::string& textureFile, int& nrRows, int& nrCols)
{
	std::ifstream file(fileName);
	if (!file) throw std::runtime_error("Invalid Level file!\n");

	std::string line{};
	std::vector<Cell> out{};

	// Get the texture of the lvl
	{
		std::getline(file, line);
		textureFile = line;
	}

	// Get the rows and cols of the lvl
	{
		std::getline(file, line);
		std::istringstream str{ line};
		str >> nrRows >> nrCols;
	}

	// Get the dimensions of 1 cell
	int cellW, cellH;
	{
		std::getline(file, line);
		std::istringstream str{ line };
		str >> cellW >> cellH;
	}

	size_t i{};
	while (std::getline(file, line))
	{
		for (size_t j = 0; j < line.size(); j++)
		{
			out.emplace_back(Cell{ SDL_Rect{ int(j * cellW * scale), int(i * cellH * scale),int(cellW * scale), int(cellH * scale) }, line[j] == '#' });
		}
		++i;
	}

	return out;
}

