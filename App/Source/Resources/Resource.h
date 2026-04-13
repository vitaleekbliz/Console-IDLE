#pragma once
#include <cstdint>

// This file creates resource enum and names (const char*) using macros for easier adding new resources.

#define RESOURCE_LIST(V) \
	V(None)              \
	V(Coal)              \
	V(CoalDust)          \
	V(IronOre)           \
	V(IronDust)          \
	V(IronIngot)         \
	V(CopperOre)         \
	V(CopperDust)        \
	V(CopperIngot)       \
	V(TinOre)            \
	V(TinDust)           \
	V(TinIngot)          \
	V(LeadOre)           \
	V(LeadDust)          \
	V(LeadIngot)         \
	V(ZincOre)           \
	V(ZincDust)          \
	V(ZincIngot)         \
	V(NickelOre)         \
	V(NickelDust)        \
	V(NickelIngot)       \
	V(GoldOre)           \
	V(GoldDust)          \
	V(GoldIngot)         \
	V(SilverOre)         \
	V(SilverDust)        \
	V(SilverIngot)       \
	V(PlatinumOre)       \
	V(PlatinumDust)      \
	V(PlatinumIngot)     \
	V(AluminumOre)       \
	V(AluminumDust)      \
	V(AluminumIngot)     \
	V(SiliconOre)        \
	V(SiliconDust)       \
	V(SiliconIngot)      \
	V(TitaniumOre)       \
	V(TitaniumDust)      \
	V(TitaniumIngot)     \
	V(MagnesiumOre)      \
	V(MagnesiumDust)     \
	V(MagnesiumIngot)    \
	V(SteelAlloy)        \
	V(BronzeAlloy)       \
	V(BrassAlloy)        \
	V(ElectrumAlloy)     \
	V(CupronickelAlloy)  \
	V(SolderAlloy)       \
	V(MagnaliumAlloy)    \
	V(FerroTitaniumAlloy)

namespace ResourceData
{
	// change the size if needed more for enum
	typedef uint8_t ResourceSize;

	// 2. Generate the String Names
	static const char* Names[] = {
#define AS_STRING(name) #name,
		RESOURCE_LIST(AS_STRING)
#undef AS_STRING
	};

} // namespace ResourceData

// 3. Generate the Enum Class
enum class Resource : ResourceData::ResourceSize
{
#define AS_ENUM(name) name,
	RESOURCE_LIST(AS_ENUM)
#undef AS_ENUM
	COUNT
};

#undef RESOURCE_LIST