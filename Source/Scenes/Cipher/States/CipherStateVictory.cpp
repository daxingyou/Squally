#include "CipherStateVictory.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/InventoryEvents.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Events/CipherEvents.h"
#include "Events/NotificationEvents.h"
#include "Scenes/Cipher/CipherPuzzleData.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItemDeserializer.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/UIResources.h"

#include "Strings/Platformer/Combat/Rewards.h"
#include "Strings/Platformer/Notifications/ItemFound.h"
#include "Strings/Menus/Return.h"

using namespace cocos2d;

CipherStateVictory* CipherStateVictory::create()
{
	CipherStateVictory* instance = new CipherStateVictory();

	instance->autorelease();

	return instance;
}

CipherStateVictory::CipherStateVictory() : super(CipherState::StateType::Victory)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	this->backdrop = LayerColor::create(Color4B(0, 0, 0, 196), visibleSize.width, visibleSize.height);
	this->rewardsMenu = Sprite::create(UIResources::Combat_VictoryMenu);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Platformer_Combat_Rewards::create());
	this->activeCipherState = nullptr;

	LocalizedLabel*	returnLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Return::create());
	LocalizedLabel*	returnLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Return::create());

	this->returnButton = ClickableTextNode::create(returnLabel, returnLabelHover, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	this->titleLabel->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->backdrop);
	this->addChild(this->rewardsMenu);
	this->addChild(this->titleLabel);
	this->addChild(this->returnButton);
}

CipherStateVictory::~CipherStateVictory()
{
}

void CipherStateVictory::onEnter()
{
	super::onEnter();

	this->rewardsMenu->setVisible(false);
	this->setVisible(false);
}

void CipherStateVictory::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->backdrop->setPosition(Vec2(-visibleSize.width / 2.0f, -visibleSize.height / 2.0f));
	this->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->titleLabel->setPositionY(392.0f);
	this->returnButton->setPositionY(-392.0f);
}

void CipherStateVictory::initializeListeners()
{
	super::initializeListeners();

	this->returnButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->runAction(Sequence::create(
			DelayTime::create(0.5f),
			CallFunc::create([=]()
			{
				CipherState::updateState(this->activeCipherState, CipherState::StateType::GameEnd);
				CipherEvents::TriggerExitCipher(CipherEvents::CipherExitArgs(true));
			}),
			nullptr
		));
	});
}

void CipherStateVictory::onBeforeStateEnter(CipherState* cipherState)
{
	super::onBeforeStateEnter(cipherState);
}

void CipherStateVictory::onStateEnter(CipherState* cipherState)
{
	super::onStateEnter(cipherState);

	this->activeCipherState = cipherState;

	this->giveRewards(cipherState);

	this->setVisible(true);
}

void CipherStateVictory::onStateReload(CipherState* cipherState)
{
	super::onStateReload(cipherState);
}

void CipherStateVictory::onStateExit(CipherState* cipherState)
{
	super::onStateExit(cipherState);

	this->setVisible(false);
}

void CipherStateVictory::giveRewards(CipherState* cipherState)
{
	std::vector<std::string> rewards = cipherState->puzzleData->getRewards();
	std::string bonusReward = cipherState->puzzleData->getBonusReward();
	std::vector<Item*> items = std::vector<Item*>();
	bool getBonusRewards = cipherState->isHardModeEnabled();

	for (auto it = rewards.begin(); it != rewards.end(); it++)
	{
		PlatformerItemDeserializer::getInstance()->deserialize(InventoryEvents::RequestItemDeserializationArgs(*it, [&](Item* item)
		{
			items.push_back(item);
		}));
	}

	if (getBonusRewards)
	{
		PlatformerItemDeserializer::getInstance()->deserialize(InventoryEvents::RequestItemDeserializationArgs(bonusReward, [&](Item* item)
		{
			items.push_back(item);
		}));
	}

	for (auto it = items.begin(); it != items.end(); it++)
	{
		Inventory* playerInventory = Inventory::create(SaveKeys::SaveKeySquallyInventory);

		NotificationEvents::TriggerNotification(NotificationEvents::NotificationArgs(Strings::Platformer_Notifications_ItemFound::create(), (*it)->getString(), (*it)->getIconResource()));

		playerInventory->forceInsert(*it);	
	}
}
