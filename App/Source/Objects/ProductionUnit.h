#pragma once
#include "Object.h"

class ProductionUnit : public Object
{
public:
	ProductionUnit() = default;
	virtual ~ProductionUnit() = default;

	virtual void render() override;

private:
};
