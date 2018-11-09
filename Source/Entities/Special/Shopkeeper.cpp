#include "Shopkeeper.h"

Shopkeeper* Shopkeeper::create()
{
	Shopkeeper* instance = new Shopkeeper();

	instance->autorelease();

	return instance;
}

Shopkeeper::Shopkeeper()
{
	this->animationNode = AnimationNode::create(Resources::Entities_Platformer_Misc_Shopkeeper_Animations);

	SpriterEngine::EntityInstance* entity = this->animationNode->play("Entity");
	entity->setCurrentAnimation("Idle");

	this->addChild(this->animationNode);
}

Shopkeeper::~Shopkeeper()
{
}