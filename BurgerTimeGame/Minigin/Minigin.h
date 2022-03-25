#pragma once
struct SDL_Window;
namespace dae
{
	class GameObject;
	class PeterPepperComponent;

	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};

		PeterPepperComponent* AddPlayer(GameObject* parent, UINT playerId, const glm::vec3& playerPos, const glm::vec3& healthDisplayPos, const glm::vec3& scoreDisplayPos) const;
	};
}