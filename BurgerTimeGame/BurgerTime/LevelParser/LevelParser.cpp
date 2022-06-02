#include "pch.h"
#include "LevelParser.h"

std::unordered_map<char, glm::vec2> LevelParser::m_LevelPieceIDs
{
	{'/'  ,{0, 0}},
	{'\\' ,{m_GridBoxSize, 0}},
	{'-'  ,{m_GridBoxSize * 2, 0}},
	{'<'  ,{m_GridBoxSize * 3, 0}},
	{'>'  ,{m_GridBoxSize * 4, 0}},
	{'p'  ,{m_GridBoxSize * 5, 0}},
	{'u'  ,{m_GridBoxSize * 6, 0}},
	{'q'  ,{m_GridBoxSize * 7, 0}},
	{'{'  ,{0, m_GridBoxSize}},
	{'}'  ,{m_GridBoxSize, m_GridBoxSize}},
	{'#'  ,{m_GridBoxSize * 2, m_GridBoxSize}},
	{'('  ,{m_GridBoxSize * 3, m_GridBoxSize}},
	{')'  ,{m_GridBoxSize * 4, m_GridBoxSize}},
	{'['  ,{0, m_GridBoxSize * 2}},
	{']'  ,{m_GridBoxSize, m_GridBoxSize * 2}},
};

std::vector<std::vector<SDL_Rect>> LevelParser::ParseFile(const std::string& fileName)
{
	std::ifstream file(fileName);

	if (!file) throw std::runtime_error("Invalid Level file!\n");

	size_t i{};
	std::vector<std::vector<SDL_Rect>> out{};

	std::string line{};
	while (std::getline(file, line))
	{
		out.emplace_back(std::vector<SDL_Rect>());
		for (size_t j = 0; j < line.size(); j++)
		{
			glm::vec2 pos = m_LevelPieceIDs[line[j]];
			out[i].emplace_back(SDL_Rect{ static_cast<int>(pos.x), static_cast<int>(pos.y), m_GridBoxSize, m_GridBoxSize });
		}
		++i;
	}

	return out;
}