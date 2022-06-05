#pragma once

enum class GameMode
{
	SINGLEPLAYER,
	MULTIPLAYER
};

class GameState final : public Singleton<GameState>
{
public:
	virtual ~GameState() override = default;
	GameState(const GameState& other) = delete;
	GameState(GameState&& other) = delete;
	GameState& operator=(const GameState& other) = delete;
	GameState& operator=(GameState&& other) = delete;
	
	void Reset(GameMode mode);

	void OnSliceCompleted();
	void OnGameLoss();
	bool LevelCompleted() { return m_LevelComplete; }

	void SetNrOfSlices(uint32_t nr) { m_NumBurgerSlices = nr; }

	const GameMode& GetGameMode() { return m_GameMode; }
private:
	friend class Singleton;
	GameState() = default;

	GameMode m_GameMode{};
	size_t m_NumBurgerSlices{};
	bool m_LevelComplete{};
};

