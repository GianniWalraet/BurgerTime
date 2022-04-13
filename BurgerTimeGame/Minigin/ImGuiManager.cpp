#include "MiniginPCH.h"
#include "ImGuiManager.h"
#include <chrono>
#include <numeric>
#include "imgui_plot.h"

void ImGuiManager::Initialize(SDL_Window* pWindow)
{
	m_pWindow = pWindow;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(pWindow, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}
void ImGuiManager::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiManager::Render()
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_pWindow);
	ImGui::NewFrame();
	RenderPlotWindows();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::HandleInput(const SDL_Event& e)
{
	ImGui_ImplSDL2_ProcessEvent(&e);
}

void ImGuiManager::RenderPlotWindows()
{
	ImGui::SetNextWindowSize({ 350,400 });
	ImGui::Begin("Exercise1");
	if (ImGui::Button("Trash The Cache"))
	{
		CacheTheTrashInt(m_DataX1, m_DataY1);
		m_Button1Active = !m_Button1Active;
	}

	if (m_Button1Active)
	{
		ImGui::PlotConfig conf{};
		conf.values.xs = &m_DataX1[0];
		conf.values.ys = &m_DataY1[0];
		conf.values.count = m_Size;
		conf.scale.min = *std::min_element(m_DataY1.begin(), m_DataY1.end());
		conf.scale.max = *std::max_element(m_DataY1.begin(), m_DataY1.end());

		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(250, 150);
		conf.line_thickness = 2.f;

		ImGui::Plot("plot", conf);
	}
	ImGui::End();


	ImGui::SetNextWindowSize({ 350,500 });
	ImGui::Begin("Exercise2");
	if (ImGui::Button("Trash The Cache with GameObject3D"))
	{
		CacheTheTrashGameObject3D(m_DataX2, m_DataY2);
		m_Button2Active = !m_Button2Active;
	}
	if (m_Button2Active)
	{
		ImGui::PlotConfig conf{};
		conf.values.xs = &m_DataX2[0];
		conf.values.ys = &m_DataY2[0];
		conf.values.count = m_Size;
		conf.scale.min = *std::min_element(m_DataY2.begin(), m_DataY2.end());
		conf.scale.max = *std::max_element(m_DataY2.begin(), m_DataY2.end());
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(200, 120);
		conf.line_thickness = 2.f;

		ImGui::Plot("plot", conf);
	}

	if (ImGui::Button("Trash The Cache with GameObject3DAlt") )
	{
		CacheTheTrashGameObject3D(m_DataX2, m_DataY2);
		CacheTheTrashGameObject3DAlt(m_DataX3, m_DataY3);
		m_Button3Active = !m_Button3Active;
	}
	if (m_Button3Active)
	{
		ImGui::PlotConfig conf{};
		conf.values.xs = &m_DataX3[0];
		conf.values.ys = &m_DataY3[0];
		conf.values.count = m_Size;
		conf.scale.min = *std::min_element(m_DataY3.begin(), m_DataY3.end());
		conf.scale.max = *std::max_element(m_DataY3.begin(), m_DataY3.end());
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(200, 120);
		conf.line_thickness = 2.f;

		ImGui::Plot("plot", conf);

		float yData1[m_Size]{};
		float yData2[m_Size]{};
		for (size_t i = 0; i < m_DataY2.size(); i++) yData1[i] = m_DataY2[i];
		for (size_t i = 0; i < m_DataY3.size(); i++) yData2[i] = m_DataY3[i];
		const float* yData[] = { yData1, yData2 };
		ImU32 colors[2] = { ImColor(0, 255, 0), ImColor(255, 0, 0) };

		conf.values.ys = nullptr;
		conf.values.xs = &m_DataX3[0];
		conf.values.ys_list = yData;
		conf.values.ys_count = 2;
		conf.values.colors = colors;
		conf.scale.min = std::min(*std::min_element(m_DataY2.begin(), m_DataY2.end()), *std::min_element(m_DataY3.begin(), m_DataY3.end()));
		conf.scale.max = std::max(*std::max_element(m_DataY2.begin(), m_DataY2.end()), *std::max_element(m_DataY3.begin(), m_DataY3.end()));

		ImGui::Plot("plot", conf);
	}

	ImGui::End();
}

void ImGuiManager::CacheTheTrashInt(std::vector<float>& dataX, std::vector<float>& dataY)
{
	dataX.clear();
	dataY.clear();

	const int arr_size = 1'000'000;
	int* arr = new int[arr_size];
	memset(arr, 0, arr_size);

	long long totalTime{};

	for (int i = 1; i <= 1024; i *= 2)
	{
		totalTime = 0;
		for (int j = 0; j < m_NrOfQueries; ++j)
		{
			const auto start = std::chrono::high_resolution_clock::now();
			for (int k = 0; k < arr_size; k += i)
			{
				arr[k] *= 2;
			}
			const auto end = std::chrono::high_resolution_clock::now();
			const auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			totalTime += elapsedTime;
		}

		const int averageTime = static_cast<int>(totalTime / m_NrOfQueries);
		dataX.push_back(static_cast<float>(i));
		dataY.push_back(static_cast<float>(averageTime));
	}
	delete[] arr;
}
void ImGuiManager::CacheTheTrashGameObject3D(std::vector<float>& dataX, std::vector<float>& dataY)
{
	dataX.clear();
	dataY.clear();

	const int arr_size = 1'000'000;
	GameObject3D* arr = new GameObject3D[arr_size];
	for (int i = 0; i < arr_size; i++) { arr[i].ID = i + 1; }

	long long totalTime{};

	for (int i = 1; i <= 1024; i *= 2)
	{
		totalTime = 0;
		for (int j = 0; j < m_NrOfQueries; ++j)
		{
			const auto start = std::chrono::high_resolution_clock::now();
			for (int k = 0; k < arr_size; k += i)
			{
				arr[k].ID *= 2;
			}
			const auto end = std::chrono::high_resolution_clock::now();
			const auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			totalTime += static_cast<int>(elapsedTime);
		}

		const int averageTime = static_cast<int>(totalTime / m_NrOfQueries);
		dataX.push_back(static_cast<float>(i));
		dataY.push_back(static_cast<float>(averageTime));
	}
	delete[] arr;
}
void ImGuiManager::CacheTheTrashGameObject3DAlt(std::vector<float>& dataX, std::vector<float>& dataY)
{
	dataX.clear();
	dataY.clear();

	const int arr_size = 1'000'000;
	GameObject3DAlt* arr = new GameObject3DAlt[arr_size];
	for (int i = 0; i < arr_size; i++) { arr[i].ID = i + 1; }

	long long totalTime{};

	for (int i = 1; i <= 1024; i *= 2)
	{
		totalTime = 0;
		for (int j = 0; j < m_NrOfQueries; ++j)
		{
			const auto start = std::chrono::high_resolution_clock::now();
			for (int k = 0; k < arr_size; k += i)
			{
				arr[k].ID *= 2;
			}
			const auto end = std::chrono::high_resolution_clock::now();
			const auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			totalTime += static_cast<int>(elapsedTime);
		}

		const int averageTime = static_cast<int>(totalTime / m_NrOfQueries);
		dataX.push_back(static_cast<float>(i));
		dataY.push_back(static_cast<float>(averageTime));
	}
	delete[] arr;
}
