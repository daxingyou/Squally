#include "SapphireBand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SapphireBand::SaveKey = "sapphire-band";

SapphireBand* SapphireBand::create()
{
	SapphireBand* instance = new SapphireBand();

	instance->autorelease();

	return instance;
}

SapphireBand::SapphireBand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 15 }}), ItemStats(
	// Health
	0,
	// Mana
	2,
	// Attack
	0,
	// Armor
	0,
	// Speed
	0.05f
))
{
}

SapphireBand::~SapphireBand()
{
}

Item* SapphireBand::clone()
{
	return SapphireBand::create();
}

std::string SapphireBand::getItemName()
{
	return SapphireBand::SaveKey;
}

LocalizedString* SapphireBand::getString()
{
	return Strings::Items_Equipment_Gear_Rings_SapphireBand::create();
}

std::string SapphireBand::getIconResource()
{
	return ItemResources::Equipment_Gear_Rings_SapphireBand;
}

std::string SapphireBand::getSerializationKey()
{
	return SapphireBand::SaveKey;
}
