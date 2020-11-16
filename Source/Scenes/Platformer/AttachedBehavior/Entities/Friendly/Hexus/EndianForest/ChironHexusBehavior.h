#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class ChironHexusBehavior : public HexusBehaviorBase
{
public:
	static ChironHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ChironHexusBehavior(GameObject* owner);
	virtual ~ChironHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
