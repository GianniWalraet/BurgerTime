#pragma once

enum class GameMode
{
	SOLO,
	COOP
};

class GameState final : public Singleton<GameState>
{
public:
	virtual ~GameState() override = default;
	GameState(const GameState& other) = delete;
	GameState(GameState&& other) = delete;
	GameState& operator=(const GameState& other) = delete;
	GameState& operator=(GameState&& other) = delete;
	
	void OnReset(GameMode mode);
	void OnRespawn();

	void OnSliceCompleted();
	void OnPlayerKill();

	bool PlayerKilled() const { return m_PlayerKilled; }
	bool LevelCompleted() const { return m_LevelComplete; }

	void SetNrOfSlices(uint32_t nr) { m_NumBurgerSlices = nr; }

	void SetScoreP1(int32_t score) { m_P1Score = score; }
	void SetScoreP2(int32_t score) { m_P2Score = score; }

	uint32_t GetScoreP1() { return m_P1Score; }
	uint32_t GetScoreP2() { return m_P2Score; }

	const GameMode& GetGameMode() { return m_GameMode; }
private:
	friend class Singleton;
	GameState() = default;

	GameMode m_GameMode{};
	size_t m_NumBurgerSlices{};

	int32_t m_P1Score{};
	int32_t m_P2Score{};

	bool m_LevelComplete{};
	bool m_PlayerKilled{};
};

