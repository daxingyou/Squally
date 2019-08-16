#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class VoidArcher : public PlatformerEnemy
{
public:
	static VoidArcher* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyVoidArcher;

private:
	typedef PlatformerEnemy super;
	VoidArcher(cocos2d::ValueMap& properties);
	~VoidArcher();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
