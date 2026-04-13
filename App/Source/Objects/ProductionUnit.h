#pragma once
#include "Object.h"
#include "Resources/ResourcesManager.h"

class ProductionUnit : public Object
{
public:
	ProductionUnit() = default;
	virtual ~ProductionUnit() = default;

private:
	ResourcesManager* m_ResourcesManager = nullptr;
};
