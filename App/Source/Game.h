#pragma once
#include "Resources/ResourcesManager.h"
#include "Engine/ConsoleRenderer.h"
#include "Objects/ObjectCreator.h"

class Game
{
public:
	void Run();

private:
	ResourcesManager m_ResourceManager;
	ObjectCreator m_ObjectCreator;
};
