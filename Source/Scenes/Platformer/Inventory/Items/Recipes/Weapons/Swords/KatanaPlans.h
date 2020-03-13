#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/SwordRecipe.h"

class KatanaPlans : public SwordRecipe
{
public:
	static KatanaPlans* create();

	Item* craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyKatanaPlans;

protected:
	KatanaPlans();
	virtual ~KatanaPlans();
	
	std::map<Item*, int> getReagentsInternal() override;

private:
	typedef SwordRecipe super;
};