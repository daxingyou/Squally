#include "FilterEntry.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Inventory/Item.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Menus/Inventory/MenuEntry.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

using namespace cocos2d;

FilterEntry::FilterEntry(LocalizedString* text, std::string spriteResource) : super(text, spriteResource)
{
}

FilterEntry::~FilterEntry()
{
}
