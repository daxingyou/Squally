////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Shen : public NpcBase
{
public:
	static Shen* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyShen;

private:
	Shen(cocos2d::ValueMap* initProperties);
	~Shen();
};
