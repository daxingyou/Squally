#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerDecorObject : public HackableObject
{
public:
	static PlatformerDecorObject* create(cocos2d::ValueMap& properties);

protected:
	PlatformerDecorObject(cocos2d::ValueMap& properties);
	virtual ~PlatformerDecorObject();

	void onEnter() override;
	void onHackerModeEnable() override;
	void onHackerModeDisable() override;
	
private:
	typedef HackableObject super;

	void runBounce();

	cocos2d::Sprite* sprite;
};
