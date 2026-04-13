#include "Game.h"

void Game::Run()
{
	m_ObjectCreator.create<ProductionUnit>();
	DebugConsole();
}

void Game::DebugConsole()
{
	std::cout << std::string(30, '-');

	ConsoleRenderer::Get().Init(200, 200);

	std::string test(16, '#');

	ConsoleRenderer::Get().Draw(3, 7, 4, 4, test);
	ConsoleRenderer::Get().Draw(-1, 7, 4, 4, test);
	ConsoleRenderer::Get().Draw(3, -1, 4, 4, test);
	ConsoleRenderer::Get().Draw(3, 7, 46, -4, test);
	ConsoleRenderer::Get().Draw(3, 7, 46, 0, test);
	ConsoleRenderer::Get().Draw(3, 7, 43443434, 4, test);

	ConsoleRenderer::Get().DrawFrame();

	ConsoleRenderer::Get().Draw(3, 7, 4, 4, test);
	ConsoleRenderer::Get().DrawFrame();
}
