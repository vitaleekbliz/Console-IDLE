#pragma once
#include <string>
#include <atomic>
#include <unordered_map>
#include "Defines.h"

enum class BaseResource : enumSize
{
	UndefinedBase = 0,
	Credits,
	Iron,
	Gold,
	Copper,
	Silver,
	Coal,
	RoseGold,
	SterlingSilver,
	WhiteGold,
	HardenedSteel
};

enum class ResourceCategory : enumSize
{
	UndefinedCategory = 0,
	System,
	Ore,
	Dust,
	Ingot,
	Alloy
};

struct Resource
{
	Resource() = default;
	Resource(const std::string& name, ResourceCategory category, uint64_t amount);

	std::string name;
	ResourceValue amount = 0;
	ResourceCategory category = ResourceCategory::UndefinedCategory;
};

class ResourcesManager
{
public:
	ResourcesManager();

	ResourceValue getBalance(BaseResource base, ResourceCategory category) const;
	bool removeBalance(BaseResource base, ResourceCategory category, ResourceValue amount);
	void addBalance(BaseResource base, ResourceCategory category, ResourceValue amount);

private:
	// Used for unordered map
	struct ResourceKey
	{
		ResourceKey(ResourceCategory category, BaseResource base);

		ResourceCategory category;
		BaseResource base;

		// Required for unordered_map
		bool operator==(const ResourceKey& other) const;
	};

	struct ResouceKeyHasher
	{
		std::size_t operator()(const ResourceKey& k) const;
	};

	// Used for config
	struct ResourceProperties
	{
		std::string name;
		std::vector<ResourceCategory> categories;
		BaseResource base;

		ResourceProperties(std::string name, BaseResource base, std::vector<ResourceCategory> categories);
	};

	[[nodiscard]] static const std::vector<ResourceProperties>& GetConfig();

	std::unordered_map<ResourceKey, Resource, ResouceKeyHasher> m_Vault;
};
