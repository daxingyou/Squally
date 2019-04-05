#include "StateGameEnd.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"

#include "Analytics/AnalyticsCategories.h"
#include "Engine/Analytics/Analytics.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/SoundManager.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Hexus/Config.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Menus/Leave.h"

using namespace cocos2d;

StateGameEnd* StateGameEnd::create()
{
	StateGameEnd* instance = new StateGameEnd();

	instance->autorelease();

	return instance;
}

StateGameEnd::StateGameEnd() : super(GameState::StateType::GameEnd)
{
	LocalizedLabel* backButtonLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Leave::create());
	LocalizedLabel* backButtonLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Leave::create());

	backButtonLabel->enableOutline(Color4B::BLACK, 2);
	backButtonLabelHover->enableOutline(Color4B::BLACK, 2);

	this->backButton = ClickableTextNode::create(
		backButtonLabel,
		backButtonLabelHover,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected
	);

	this->backButton->setOpacity(0);

	this->addChild(this->backButton);
}

StateGameEnd::~StateGameEnd()
{
}

void StateGameEnd::onEnter()
{
	super::onEnter();

	this->backButton->setOpacity(0);
}

void StateGameEnd::initializeListeners()
{
	super::initializeListeners();
}

void StateGameEnd::initializePositions()
{
	super::initializePositions();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->backButton->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 196.0f);
}

void StateGameEnd::onBackClick(GameState* gameState)
{
	GameState::updateState(gameState, GameState::StateType::EmptyState);

	std::string winsKey = HexusOpponentData::winsPrefix + gameState->opponentData->enemyNameKey;
	std::string lossesKey = HexusOpponentData::lossesPrefix + gameState->opponentData->enemyNameKey;

	Analytics::sendEvent(AnalyticsCategories::Hexus, "game_duration", gameState->opponentData->enemyNameKey, gameState->gameDurationInSeconds);
	bool isDraw = gameState->playerLosses >= 2 && gameState->enemyLosses >= 2;
	bool isWin = gameState->playerLosses < 2 && gameState->enemyLosses >= 2;
	int reward = gameState->opponentData->reward;
	bool isLastInChapter = gameState->opponentData->getIsLastInChapter();

	if (isDraw)
	{
		int losses = SaveManager::getGlobalDataOrDefault(winsKey, cocos2d::Value(0)).asInt() + 1;

		SaveManager::saveGlobalData(lossesKey, cocos2d::Value(losses));

		// Analytics for losing
		Analytics::sendEvent(AnalyticsCategories::Hexus, "total_losses", gameState->opponentData->enemyNameKey, losses);

		if (gameState->opponentData->stateOverride == nullptr)
		{
			// Half the reward for a draw
			NavigationEvents::navigateHexusRewards(NavigationEvents::NavigateHexusRewardArgs(reward / 2, true));
		}
		else
		{
			NavigationEvents::navigateBack();
		}
	}
	else if (isWin)
	{
		int wins = SaveManager::getGlobalDataOrDefault(winsKey, cocos2d::Value(0)).asInt() + 1;
		int losses = SaveManager::getGlobalDataOrDefault(winsKey, cocos2d::Value(0)).asInt();

		SaveManager::saveGlobalData(winsKey, cocos2d::Value(wins));

		if (wins == 1 && losses == 0)
		{
			Analytics::sendEvent(AnalyticsCategories::Hexus, "first_game_result", gameState->opponentData->enemyNameKey, 1);

			if (isLastInChapter)
			{
				// 8x bonus for first chapter clear
				reward = int(float(reward) * 8.0f);
			}
			else
			{
				// 2x bonus for first clear
				reward = int(float(reward) * 2.0f);
			}
		}

		if (wins == 1)
		{
			Analytics::sendEvent(AnalyticsCategories::Hexus, "attempts_for_first_win", gameState->opponentData->enemyNameKey, losses + wins);
		}

		// Analytics for winning
		Analytics::sendEvent(AnalyticsCategories::Hexus, "total_wins", gameState->opponentData->enemyNameKey, wins);


		if (gameState->opponentData->stateOverride == nullptr)
		{
			NavigationEvents::navigateHexusRewards(NavigationEvents::NavigateHexusRewardArgs(reward, false, isLastInChapter));
		}
		else
		{
			NavigationEvents::navigateBack();
		}
	}
	else
	{
		int wins = SaveManager::getGlobalDataOrDefault(winsKey, cocos2d::Value(0)).asInt();
		int losses = SaveManager::getGlobalDataOrDefault(winsKey, cocos2d::Value(0)).asInt() + 1;

		SaveManager::saveGlobalData(lossesKey, cocos2d::Value(losses));

		if (wins == 0 && losses == 1)
		{
			Analytics::sendEvent(AnalyticsCategories::Hexus, "first_game_result", gameState->opponentData->enemyNameKey, 0);
		}

		// Analytics for losing
		Analytics::sendEvent(AnalyticsCategories::Hexus, "total_losses", gameState->opponentData->enemyNameKey, losses);

		NavigationEvents::navigateBack();
	}
}

void StateGameEnd::onBeforeStateEnter(GameState* gameState)
{
	super::onBeforeStateEnter(gameState);
}

void StateGameEnd::onStateEnter(GameState* gameState)
{
	super::onStateEnter(gameState);

	if (gameState->playerLosses >= 2)
	{
		SoundManager::playSoundResource(SoundResources::Hexus_Defeat);
	}
	else if (gameState->enemyLosses >= 2)
	{
		SoundManager::playSoundResource(SoundResources::Hexus_Victory);
	}

	this->backButton->enableInteraction(0);
	this->backButton->runAction(FadeTo::create(Config::replaceEndButtonFadeSpeed, 255));
	this->backButton->setMouseClickCallback(CC_CALLBACK_0(StateGameEnd::onBackClick, this, gameState));
}

void StateGameEnd::onStateReload(GameState* gameState)
{
	super::onStateReload(gameState);
}

void StateGameEnd::onStateExit(GameState* gameState)
{
	super::onStateExit(gameState);

	this->backButton->disableInteraction(0);
	this->backButton->setMouseClickCallback(nullptr);
}
