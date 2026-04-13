#pragma once
#include "Defines.h"
#include "Resource.h"
#include "Logging/Logging.h"
#include <vector>

class ResourcesManager
{
public:
	ResourcesManager();

	ResourceValue getBalance(Resource resource) const;
	bool removeBalance(Resource resource, ResourceValue amount);
	void addBalance(Resource resource, ResourceValue amount);
	const char* getName(Resource resource);

private:
	std::vector<ResourceValue> m_Vault;
};
