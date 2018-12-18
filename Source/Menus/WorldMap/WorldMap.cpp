#include "WorldMap.h"

#include "Resources/MapResources.h"
WorldMap* WorldMap::instance = nullptr;

const std::string WorldMap::StringKeySelectLevel = "Menu_Story_Select_Level";
const std::string WorldMap::StringKeyLevelNameJungle = "Menu_Story_Level_Name_Jungle";
const std::string WorldMap::StringKeyLevelNameAquaticRuins = "Menu_Story_Level_Name_Aquatic_Ruins";
const std::string WorldMap::StringKeyLevelNameForest = "Menu_Story_Level_Name_Forest";
const std::string WorldMap::StringKeyLevelNameCaverns = "Menu_Story_Level_Name_Caverns";
const std::string WorldMap::StringKeyLevelNameCastle = "Menu_Story_Level_Name_Castle";
const std::string WorldMap::StringKeyLevelNameIceCaps = "Menu_Story_Level_Name_Ice_Caps";
const std::string WorldMap::StringKeyLevelNameObelisk = "Menu_Story_Level_Name_Obelisk";
const std::string WorldMap::StringKeyLevelNameVolcano = "Menu_Story_Level_Name_Volcano";
const std::string WorldMap::StringKeyLevelNameMech = "Menu_Story_Level_Name_Mech";

void WorldMap::registerGlobalScene()
{
	if (WorldMap::instance == nullptr)
	{
		WorldMap::instance = new WorldMap();

		WorldMap::instance->autorelease();
		WorldMap::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(WorldMap::instance);
}

WorldMap::WorldMap()
{
	this->mapNodes = std::vector<MapNode*>();
	this->mouse = Mouse::create();
	this->background = Sprite::create(UIResources::Menus_WorldMap_WorldMap);

	this->hud = Hud::create();

	this->forest = MapNode::create(
		Localization::resolveString(WorldMap::StringKeyLevelNameForest),
		MapResources::Forest_Forest
	);

	this->waterRuins = MapNode::create(
		Localization::resolveString(WorldMap::StringKeyLevelNameAquaticRuins),
		MapResources::AquaticRuins_AquaticRuins
	);

	this->caverns = MapNode::create(
		Localization::resolveString(WorldMap::StringKeyLevelNameCaverns),
		MapResources::Caverns_Caverns
	);

	this->castle = MapNode::create(
		Localization::resolveString(WorldMap::StringKeyLevelNameCastle),
		MapResources::Castle_Castle
	);

	this->iceCaps = MapNode::create(
		Localization::resolveString(WorldMap::StringKeyLevelNameIceCaps),
		MapResources::IceCaps_IceCaps
	);

	this->volcano = MapNode::create(
		Localization::resolveString(WorldMap::StringKeyLevelNameVolcano),
		MapResources::Volcano_Volcano
	);

	this->crypts = MapNode::create(
		Localization::resolveString(WorldMap::StringKeyLevelNameObelisk),
		MapResources::Obelisk_Obelisk
	);

	this->voidStar = MapNode::create(
		Localization::resolveString(WorldMap::StringKeyLevelNameMech),
		MapResources::Mech_Mech
	);

	this->background->setAnchorPoint(Vec2(0.0f, 0.0f));

	this->hud->addChild(this->mouse);
	this->addChild(this->background);
	this->addChild(this->forest);
	this->addChild(this->waterRuins);
	this->addChild(this->caverns);
	this->addChild(this->castle);
	this->addChild(this->iceCaps);
	this->addChild(this->volcano);
	this->addChild(this->crypts);
	this->addChild(this->voidStar);
	this->addChild(this->hud);
}

WorldMap::~WorldMap()
{
}

void WorldMap::onEnter()
{
	GlobalScene::onEnter();

	const float delay = 0.5f;
	const float duration = 0.75f;

	GameCamera::getInstance()->setBounds(Rect(0.0f, 0.0f, this->background->getContentSize().width, this->background->getContentSize().height));

	CameraTrackingData trackingData = CameraTrackingData(this->mouse, Vec2(480.0f, 270.0f));
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// Because the mouse is a HUD object (and thus unaffected by the camera position), we need a custom function for getting the position to help with camera tracking
	trackingData.customPositionFunction = [=]()
	{
		return this->mouse->getPosition() + GameCamera::getInstance()->getCameraPosition() - visibleSize / 2.0f;
	};

	GameCamera::getInstance()->setTarget(trackingData);
}

void WorldMap::initializePositions()
{
	GlobalScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->forest->setPosition(Vec2(visibleSize.width / 2.0f - 503.0f, visibleSize.height / 2.0f + 698.0f + 224.0f));
	this->waterRuins->setPosition(Vec2(visibleSize.width / 2.0f - 552.0f, visibleSize.height / 2.0f + 255.0f + 224.0f));
	this->caverns->setPosition(Vec2(visibleSize.width / 2.0f - 413.0f, visibleSize.height / 2.0f - 143.0f + 224.0f));
	this->castle->setPosition(Vec2(visibleSize.width / 2.0f + 256.0f, visibleSize.height / 2.0f - 274.0f + 224.0f));
	this->iceCaps->setPosition(Vec2(visibleSize.width / 2.0f + 1117.0f, visibleSize.height / 2.0f - 390.0f + 224.0f));
	this->volcano->setPosition(Vec2(visibleSize.width / 2.0f + 1068.0f, visibleSize.height / 2.0f + 455.0f + 224.0f));
	this->crypts->setPosition(Vec2(visibleSize.width / 2.0f + 340.0f, visibleSize.height / 2.0f + 645.0f + 224.0f));
	this->voidStar->setPosition(Vec2(visibleSize.width / 2.0f + 760.0f, visibleSize.height / 2.0f + 44.0f + 224.0f));

	this->initializedLocked();
}

void WorldMap::initializeListeners()
{
	GlobalScene::initializeListeners();

	WorldMap::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateWorldMap, [](EventCustom* args)
	{
		GlobalDirector::loadScene(WorldMap::instance);
	}));

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(WorldMap::onKeyPressed, this);

	this->addEventListener(keyboardListener);
}

void WorldMap::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!GameUtils::isVisible(this))
	{
		return;
	}

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		{
			event->stopPropagation();
			NavigationEvents::navigateBack();
			break;
		}
		default:
		{
			break;
		}
	}
}

void WorldMap::initializedLocked()
{
	/*
	this->jungle->setLocked(false);
	this->waterRuins->setLocked(false);
	this->forest->setLocked(false);
	this->caverns->setLocked(false);
	this->castle->setLocked(false);
	this->iceCaps->setLocked(false);
	this->obelisk->setLocked(false);
	this->volcano->setLocked(false);
	this->mech->setLocked(false);*/
}
