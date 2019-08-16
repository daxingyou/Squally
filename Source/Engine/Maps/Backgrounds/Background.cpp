#include "Background.h"

#include "Engine/UI/HUD/Hud.h"

using namespace cocos2d;

const std::string Background::MapKeyBackgroundType = "background";

Background* Background::create(ValueMap& properties, std::string name, Node* child)
{
	Background* instance = new Background(properties, name, child);

	instance->autorelease();

	return instance;
}

Background::Background(ValueMap& properties, std::string name, Node* child) : MapLayer(properties, name, Background::MapKeyBackgroundType)
{
	this->background = Hud::create();

	child->setAnchorPoint(Vec2::ZERO);

	this->background->addChild(child);
	this->addChild(this->background);
}

Background::~Background()
{
}
