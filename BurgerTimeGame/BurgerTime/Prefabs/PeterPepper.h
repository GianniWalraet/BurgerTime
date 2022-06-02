#pragma once

class PeterPepper final : public GameObject
{
public:
	PeterPepper() = default;
	virtual ~PeterPepper() override { --m_PlayerID; }
	PeterPepper(const PeterPepper& other) = delete;
	PeterPepper(PeterPepper&& other) = delete;
	PeterPepper& operator=(const PeterPepper& other) = delete;
	PeterPepper& operator=(PeterPepper&& other) = delete;

protected:
	void Initialize() override;
private:
	static uint8_t m_PlayerID;
	static uint8_t m_MaxPlayers;
};

