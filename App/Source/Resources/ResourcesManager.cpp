#include "ResourcesManager.h"

static std::string ToString(ResourceCategory category)
{
	// clang-format off
	switch (category)
    {
        case ResourceCategory::UndefinedCategory: return "Undefined";
        case ResourceCategory::System:            return "System";
        case ResourceCategory::Ore:               return "Ore";
        case ResourceCategory::Dust:              return "Dust";
        case ResourceCategory::Ingot:             return "Ingot";
        case ResourceCategory::Alloy:             return "Alloy";
    }
	// clang-format on

	WARN("Failed to fetch resource category string");

	return "";
}

static std::string ToString(BaseResource base)
{
	// clang-format off
	switch (base)
	{
		case BaseResource::UndefinedBase:   return "Undefined";
		case BaseResource::Credits:         return "Credits";
		case BaseResource::Iron:            return "Iron";
		case BaseResource::Gold:            return "Gold";
		case BaseResource::Copper:          return "Copper";
		case BaseResource::Silver:          return "Silver";
		case BaseResource::Coal:            return "Coal";
		case BaseResource::RoseGold:        return "Rose Gold";
		case BaseResource::SterlingSilver:  return "Sterling Silver";
		case BaseResource::WhiteGold:       return "White Gold";
		case BaseResource::HardenedSteel:   return "Hardened Steel";
	}
	// clang-format on

	WARN("Failed to fetch resource base type string");

	return "";
}

Resource::Resource(const std::string& name, ResourceCategory category, uint64_t amount)
	: name(name), category(category), amount(amount)
{
}

ResourcesManager::ResourcesManager()
{
	const std::vector<ResourceProperties>& config = GetConfig();

	for (const ResourceProperties& prop : config)
	{
		for (const ResourceCategory& category : prop.categories)
		{
			ResourcesManager::ResourceKey key(category, prop.base);

			std::string displayName = prop.name;

			// Add category suffix
			displayName += " " + ToString(category);

			m_Vault.emplace(key, Resource(displayName, category, 0));

			TRACE("Added resource to vault. Category : (%s) \t Base : (%s)", ToString(key.category).c_str(), ToString(key.base).c_str());
		}
	}
}

ResourceValue ResourcesManager::getBalance(BaseResource base, ResourceCategory category) const
{
	ResourceValue amount = 0;
	ResourceKey key(category, base);

	if (!m_Vault.count(key))
	{
		ERROR("Vault doesn't have item with key - %s : %s, %s", __FUNCTION__, ToString(key.category).c_str(), ToString(key.base).c_str());
		return 0;
	}

	return m_Vault.at(key).amount;
}

bool ResourcesManager::removeBalance(BaseResource base, ResourceCategory category, ResourceValue amount)
{
	ResourceKey key(category, base);

	if (!m_Vault.count(key))
	{
		ERROR("Vault doesn't have item with key - %s : %s, %s", __FUNCTION__, ToString(key.category).c_str(), ToString(key.base).c_str());
		return false;
	}

	if (amount > m_Vault[key].amount)
	{
		WARN("Trying to substract more then available - %s : %s, %s", __FUNCTION__, ToString(key.category).c_str(), ToString(key.base).c_str());
		return false;
	}

	TRACE("%s %llu from vault key: %s, %s", __FUNCTION__, amount, ToString(key.category).c_str(), ToString(key.base).c_str());
	m_Vault[key].amount -= amount;
	return true;
}

void ResourcesManager::addBalance(BaseResource base, ResourceCategory category, ResourceValue amount)
{
	ResourceKey key(category, base);

	if (!m_Vault.count(key))
	{
		ERROR("Vault doesn't have item with key - %s : %s, %s", __FUNCTION__, ToString(key.category).c_str(), ToString(key.base).c_str());
		return;
	}

	TRACE("%s %llu to vault key : %s, %s", __FUNCTION__, amount, ToString(key.category).c_str(), ToString(key.base).c_str());
	m_Vault[key].amount += amount;
}

ResourcesManager::ResourceKey::ResourceKey(ResourceCategory category, BaseResource base)
	: category(category), base(base)
{
}

bool ResourcesManager::ResourceKey::operator==(const ResourceKey& other) const
{
	return base == other.base && category == other.category;
}

std::size_t ResourcesManager::ResouceKeyHasher::operator()(const ResourceKey& k) const
{
	return (std::hash<enumSize>{}(static_cast<enumSize>(k.base))) ^ (std::hash<enumSize>{}(static_cast<enumSize>(k.category)) << sizeof(enumSize));
}

ResourcesManager::ResourceProperties::ResourceProperties(std::string name, BaseResource base, std::vector<ResourceCategory> categories)
	: name(std::move(name)), categories(std::move(categories)), base(base)
{
}

const std::vector<ResourcesManager::ResourceProperties>& ResourcesManager::GetConfig()
{
	using enum BaseResource;
	using enum ResourceCategory;

	// Static ensures the vector is created once and lives for the program's duration
	static std::vector<ResourcesManager::ResourceProperties> config;

	if (config.empty())
	{
		config.reserve(10);

		// System / Currencies
		config.emplace_back("Credits", Credits, std::vector<ResourceCategory>{ System });

		// Base Metals (Mining -> Refining -> Smelting)
		config.emplace_back("Iron", Iron, std::vector<ResourceCategory>{ Ore, Dust, Ingot });
		config.emplace_back("Copper", Copper, std::vector<ResourceCategory>{ Ore, Dust, Ingot });
		config.emplace_back("Silver", Silver, std::vector<ResourceCategory>{ Ore, Dust, Ingot });
		config.emplace_back("Gold", Gold, std::vector<ResourceCategory>{ Ore, Dust, Ingot });

		// Fuel
		config.emplace_back("Coal", Coal, std::vector<ResourceCategory>{ Ore, Dust });

		// Advanced Alloys (Only exist as Alloys)
		config.emplace_back("Rose Gold", RoseGold, std::vector<ResourceCategory>{ Alloy });
		config.emplace_back("Sterling Silver", SterlingSilver, std::vector<ResourceCategory>{ Alloy });
		config.emplace_back("White Gold", WhiteGold, std::vector<ResourceCategory>{ Alloy });
		config.emplace_back("Hardened Steel", HardenedSteel, std::vector<ResourceCategory>{ Alloy });
	}

	return config;
}
