#include "EntityBehaviors.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehaviors/Entities/Collision/EntityCollisionBehaviors.h"
#include "Scenes/Platformer/AttachedBehaviors/Entities/EntityDebugBehaviors.h"

using namespace cocos2d;

const std::string EntityBehaviors::MapKeyAttachedBehavior = "entity";

EntityBehaviors* EntityBehaviors::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	EntityBehaviors* instance = new EntityBehaviors(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

EntityBehaviors::EntityBehaviors(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs, {
	EntityCollisionBehaviors::create(owner, attachedBehaviorArgs),
	EntityDebugBehaviors::create(owner, attachedBehaviorArgs),
	})
{
}

EntityBehaviors::~EntityBehaviors()
{
}

void EntityBehaviors::onLoad()
{
}
