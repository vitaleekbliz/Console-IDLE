#include "Game.h"

#include <chrono>
#include <Objects/ProductionUnit.h>
#include <thread>

void Game::Run()
{
	// 1. Test memory arena
	ProductionUnit* first = m_ObjectCreator.create<ProductionUnit>();
	Object* second = m_ObjectCreator.create<Object>();

	first->render();
	second->render();

	first = m_ObjectCreator.create<ProductionUnit>();

	std::this_thread::sleep_for(std::chrono::seconds(3));

	// 1.1 Subtest memory cleanup
	{
		ObjectCreator objCreator = ObjectCreator();
		objCreator.create<ProductionUnit>();
		objCreator.create<ProductionUnit>();
		objCreator.create<ProductionUnit>();
	}

	// 2. Test Console Renderer
	ConsoleRenderer::Get().Init(128, 64);

	std::string test(15, '#');
	std::string fpsCountString = "FPS : ";
	std::string currentFPS;

	auto prev = std::chrono::steady_clock::now();

	// Game Loop
	while (true)
	{
		auto now = std::chrono::steady_clock::now();
		auto frameTime = now - prev;
		prev = now;

		std::chrono::duration<double> diff = frameTime;
		double seconds = diff.count();
		double fps = 1.l / seconds;

		currentFPS = std::to_string((int)std::floor(fps));

		ConsoleRenderer::Get().Draw(2, 2, fpsCountString.size(), 1, fpsCountString);

		ConsoleRenderer::Get().Draw(fpsCountString.size() + 3, 2, currentFPS.size(), 1, currentFPS);

		ConsoleRenderer::Get().Draw(5, 17, 5, 3, test);
		ConsoleRenderer::Get().Draw(45, 47, 5, 3, test);
		ConsoleRenderer::Get().Draw(65, 37, 5, 3, test);
		ConsoleRenderer::Get().Draw(25, 37, 5, 3, test);
		ConsoleRenderer::Get().Draw(15, 7, 5, 3, test);
		ConsoleRenderer::Get().DrawFrame();
	}
}
