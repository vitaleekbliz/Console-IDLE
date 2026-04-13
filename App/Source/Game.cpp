#include "Game.h"

void Game::Run()
{
	m_ObjectCreator.create<ProductionUnit>();
	DebugConsole();
}

void Game::DebugConsole()
{
	std::string obj = "Hello World!\nThis is a debug console.\nYou can write anything here.";
	// consoleRenderer_.Draw(0, 0, 0, 0, obj);
}
