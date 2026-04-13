#pragma once
#include "Resources/ResourcesManager.h"
#include "Engine/ConsoleRenderer.h"
#include "Objects/ObjectCreator.h"
#include "Objects/ProductionUnit.h"

class Game
{
public:
	void Run();

private:
	void DebugConsole();

	ResourcesManager m_ResourceManager;
	ObjectCreator m_ObjectCreator;
};
