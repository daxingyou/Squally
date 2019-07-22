#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedReindeer : public CagedAnimal
{
public:
	static CagedReindeer* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedReindeer;

protected:
	CagedReindeer(cocos2d::ValueMap& initProperties);
	virtual ~CagedReindeer();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};
