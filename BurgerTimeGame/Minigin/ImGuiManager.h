#pragma once
#include "Singleton.h"
#include <vector>


	class ImGuiManager : public Singleton<ImGuiManager>
	{
	public:
		void Initialize(SDL_Window* pWindow);
		void Destroy();

		void Render();
		void HandleInput(const SDL_Event& e);
	private:
		SDL_Window* m_pWindow{};


		static const int m_Size = 11;
		static const int m_NrOfQueries = 10;

		std::vector<float> m_DataX1, m_DataY1;
		std::vector<float> m_DataX2, m_DataY2;
		std::vector<float> m_DataX3, m_DataY3;
		bool m_Button1Active{ false }, m_Button2Active{ false }, m_Button3Active{ false };

		void RenderPlotWindows();

		void CacheTheTrashInt(std::vector<float>& dataX, std::vector<float>& dataY);
		void CacheTheTrashGameObject3D(std::vector<float>& dataX, std::vector<float>& dataY);
		void CacheTheTrashGameObject3DAlt(std::vector<float>& dataX, std::vector<float>& dataY);

		struct Transform
		{
			float matrix[16] =
			{
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1
			};
		};
		class GameObject3D
		{
		public:
			Transform transform;
			int ID;
		};
		class GameObject3DAlt
		{
		public:
			Transform* transform;
			int ID;
		};
	};



