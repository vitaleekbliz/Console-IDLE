#pragma once
#include "Resources/ResourcesManager.h"
#include "Engine/ConsoleRenderer.h"

class Game
{
public:
	void Run();
	void DebugConsole();

private:
	ResourcesManager m_ResourceManager;
};
