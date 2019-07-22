#include "CagedSquid.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CagedSquid::MapKeyCagedSquid = "caged-squid";

CagedSquid* CagedSquid::create(ValueMap& initProperties)
{
	CagedSquid* instance = new CagedSquid(initProperties);

	instance->autorelease();

	return instance;
}

CagedSquid::CagedSquid(ValueMap& initProperties) : super(initProperties, SaveKeys::SaveKeyCollectableAnimalSquid)
{
	this->animalSprite = Sprite::create(ObjectResources::Collectables_Animals_Squid);

	this->animalNode->addChild(this->animalSprite);
}

CagedSquid::~CagedSquid()
{
}

void CagedSquid::initializePositions()
{
	super::initializePositions();

	this->animalSprite->setPosition(Vec2(0.0f, -16.0f));
}
