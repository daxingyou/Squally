#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Elriel : public PlatformerFriendly
{
public:
	static Elriel* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyElriel;

private:
	typedef PlatformerFriendly super;
	Elriel(cocos2d::ValueMap& properties);
	~Elriel();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
