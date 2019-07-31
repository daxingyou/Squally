#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedCrocodile : public CagedAnimal
{
public:
	static CagedCrocodile* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedCrocodile;

protected:
	CagedCrocodile(cocos2d::ValueMap& initProperties);
	virtual ~CagedCrocodile();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};