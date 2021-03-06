#include "BoneBowPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BoneBowPlans::SaveKey = "bone-bow-plans";

BoneBowPlans* BoneBowPlans::create()
{
	BoneBowPlans* instance = new BoneBowPlans();

	instance->autorelease();

	return instance;
}

BoneBowPlans::BoneBowPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

BoneBowPlans::~BoneBowPlans()
{
}

Item* BoneBowPlans::craft()
{
	return BoneBow::create();
}

std::vector<std::tuple<Item*, int>> BoneBowPlans::getReagentsInternal()
{
	return
	{
		{ DarkWood::create(), 8 },
		{ Obsidian::create(), 4 },
	};
}

Item* BoneBowPlans::clone()
{
	return BoneBowPlans::create();
}

std::string BoneBowPlans::getItemName()
{
	return BoneBowPlans::SaveKey;
}

LocalizedString* BoneBowPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_BoneBow::create();
}

std::string BoneBowPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string BoneBowPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Bows_BoneBow;
}

std::string BoneBowPlans::getSerializationKey()
{
	return BoneBowPlans::SaveKey;
}
