#pragma once


class LevelParser final
{
public:
	static std::vector<std::vector<SDL_Rect>> ParseFile(const std::string& fileName);
private:
	static std::unordered_map<char, glm::vec2> m_LevelPieceIDs;
	static const int m_GridBoxSize = 8;
};

