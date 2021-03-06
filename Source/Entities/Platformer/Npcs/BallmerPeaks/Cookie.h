#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Cookie : public PlatformerFriendly
{
public:
	static Cookie* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Cookie(cocos2d::ValueMap& properties);
	virtual ~Cookie();

private:
	typedef PlatformerFriendly super;
};
