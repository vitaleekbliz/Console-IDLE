#include "Game.h"

void Game::Run()
{
	m_ObjectCreator.create<ProductionUnit>();
	DebugConsole();
}

void Game::DebugConsole()
{
	std::cout << std::string(30, '-');

	ConsoleRenderer::Get().Init(128, 64);

	std::string test(16, '#');

	ConsoleRenderer::Get().Draw(5, 7, 4, 4, test);
	ConsoleRenderer::Get().DrawBorder();
	ConsoleRenderer::Get().DrawFrame();
}
