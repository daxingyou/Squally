#pragma once

#include "Engine/Inventory/Inventory.h"

class Equipable;
class Gear;
class Hat;
class Offhand;
class Weapon;

// Generic inventory for any set of equipment with convenience methods
class EquipmentInventory : public Inventory
{
public:
	static EquipmentInventory* create(std::string saveKey = "", int capacity = Inventory::InfiniteCapacity);

	std::vector<Equipable*> getEquipment();
	Weapon* getWeapon();
	Offhand* getOffhand();
	Hat* getHat();
	std::vector<Gear*> getGear();

	int getTotalMinAttack();
	int getTotalMaxAttack();
	int getTotalDefense();

protected:
	EquipmentInventory(std::string saveKey = "", int capacity = Inventory::InfiniteCapacity);
	virtual ~EquipmentInventory();

	void onEnter() override;
	void initializeListeners() override;

private:
	typedef Inventory super;
};
