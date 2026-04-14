#include "ResourcesManager.h"

ResourcesManager::ResourcesManager()
{
	m_Vault.resize(static_cast<size_t>(Resource::COUNT));
}

ResourceValue ResourcesManager::getBalance(Resource resource) const
{
	ResourceData::ResourceSize resourceID = static_cast<ResourceData::ResourceSize>(resource);

	if (!resourceID)
	{
		APP_ERROR("Vault doesn't have item with key - %s : %s", __FUNCTION__, ResourceData::Names[resourceID]);
		return 0;
	}
	return m_Vault[resourceID];
}

bool ResourcesManager::removeBalance(Resource resource, ResourceValue amount)
{
	ResourceData::ResourceSize resourceID = static_cast<ResourceData::ResourceSize>(resource);

	if (!resourceID)
	{
		APP_ERROR("Vault doesn't have item with key - %s : %s", __FUNCTION__, ResourceData::Names[resourceID]);
		return false;
	}

	if (amount > m_Vault[resourceID])
	{
		APP_WARN("Trying to substract more then available - %s : %s", __FUNCTION__, ResourceData::Names[resourceID]);
		return false;
	}

	APP_TRACE("%s %llu from vault key: %s", __FUNCTION__, amount, ResourceData::Names[resourceID]);
	m_Vault[resourceID] -= amount;
	return true;
}

void ResourcesManager::addBalance(Resource resource, ResourceValue amount)
{
	ResourceData::ResourceSize resourceID = static_cast<ResourceData::ResourceSize>(resource);

	if (!resourceID)
	{
		APP_ERROR("Vault doesn't have item with key - %s : %s", __FUNCTION__, ResourceData::Names[resourceID]);
		return;
	}

	APP_TRACE("%s %llu to vault key : %s", __FUNCTION__, amount, ResourceData::Names[resourceID]);
	m_Vault[resourceID] += amount;
}

const char* ResourcesManager::getName(Resource resource)
{
	ResourceData::ResourceSize id = static_cast<ResourceData::ResourceSize>(resource);
	return ResourceData::Names[id];
}
