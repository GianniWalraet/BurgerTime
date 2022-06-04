#pragma once


class GameState final : public Singleton<GameState>
{
public:
	virtual ~GameState() override = default;
	GameState(const GameState& other) = delete;
	GameState(GameState&& other) = delete;
	GameState& operator=(const GameState& other) = delete;
	GameState& operator=(GameState&& other) = delete;
	
	void OnSliceCompleted();
	void OnGameWin();
	void OnGameLoss();
private:
	friend class Singleton;
	GameState() = default;

	size_t m_NumBurgerSlices{};
};

