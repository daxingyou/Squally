#include "HexusOpponentGramps.h"

const std::string HexusOpponentGramps::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GRAMPS";
HexusOpponentGramps* HexusOpponentGramps::instance = nullptr;

HexusOpponentGramps* HexusOpponentGramps::getInstance()
{
	if (HexusOpponentGramps::instance == nullptr)
	{
		HexusOpponentGramps::instance = new HexusOpponentGramps();
	}

	return HexusOpponentGramps::instance;
}

HexusOpponentGramps::HexusOpponentGramps() : HexusOpponentData(
	EntityResources::Npcs_EndianForest_Gramps_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	0.85f,
	Vec2(-32.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentGramps::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.14f),
	HexusOpponentData::generateDeck(25, 0.14f,
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
			CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName->at(CardKeys::Addition),
			CardList::getInstance()->cardListByName->at(CardKeys::Addition),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
		})
	)
{
}

HexusOpponentGramps::~HexusOpponentGramps()
{
}
