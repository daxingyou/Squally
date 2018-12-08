#include "LoadingScreen.h"

LoadingScreen* LoadingScreen::instance = nullptr;

void LoadingScreen::registerGlobalScene()
{
	if (LoadingScreen::instance == nullptr)
	{
		LoadingScreen::instance = new LoadingScreen();

		LoadingScreen::instance->autorelease();
		LoadingScreen::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(LoadingScreen::instance);
}

LoadingScreen::LoadingScreen()
{
	this->backgroundNode = Node::create();
	this->progressBar = CProgressBar::create();

	this->addChild(this->backgroundNode);
	this->addChild(this->progressBar);
	this->addChild(Mouse::create());
}

LoadingScreen::~LoadingScreen()
{
}

void LoadingScreen::onEnter()
{
	GlobalScene::onEnter();

	this->backgroundNode->addChild(MenuBackground::claimInstance());
}

void LoadingScreen::initializePositions()
{
	GlobalScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->progressBar->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 480.0f));
}

void LoadingScreen::initializeListeners()
{
	GlobalScene::initializeListeners();

	instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateLoadingScreen, [](EventCustom* args)
	{
		GlobalDirector::loadScene(LoadingScreen::instance);
	}));
}

void LoadingScreen::loadLevel(std::string levelFile, const std::function<void(SerializableMap*)> newOnLoadCallback)
{
	this->totalFileCount = 0;
	this->loadedFileCount = 0;
	this->currentLevelFile = levelFile;
	this->onLoadCallback = newOnLoadCallback;

	this->map = SerializableMap::deserialize(levelFile);
	this->map->retain();

	// Asyncronously get all files under the game, and load them
	FileUtils::getInstance()->listFilesRecursivelyAsync(FileUtils::getInstance()->getDefaultResourceRootPath(), CC_CALLBACK_1(LoadingScreen::onFileEnumerationComplete, this));
}

void LoadingScreen::onFileEnumerationComplete(std::vector<std::string> files)
{
	// TEMP DEBUG: Remove this to re-enable loading screen
	if (this->onLoadCallback != nullptr)
	{
		this->onLoadCallback(this->map);
		return;
	}

	auto textureLoadCallback = CC_CALLBACK_1(LoadingScreen::onTextureAssetLoaded, this);
	auto soundLoadCallback = CC_CALLBACK_0(LoadingScreen::onSoundAssetLoaded, this);

	for (auto it = files.begin(); it != files.end(); it++)
	{
		std::string file = *it;

		if (LoadingScreen::isPreloadableImage(file) ||
			LoadingScreen::isPreloadableSound(file))
		{
			this->totalFileCount++;
		}
	}

	for (auto it = files.begin(); it != files.end(); it++)
	{
		std::string file = *it;

		if (LoadingScreen::isPreloadableImage(file))
		{
			// Load texture
			Director::getInstance()->getTextureCache()->addImageAsync(file, textureLoadCallback);
		}
		else if (LoadingScreen::isPreloadableSound(file))
		{
			// Load sound
			AudioEngine::preload(file, soundLoadCallback);
		}
	}

	// In case there are no assets to load we also need to check here
	this->enterLevelIfDoneLoading();
}

void LoadingScreen::onTextureAssetLoaded(Texture2D* asset)
{
	this->incrementLoadedFileCount();
	this->enterLevelIfDoneLoading();
}

void LoadingScreen::onSoundAssetLoaded()
{
	this->incrementLoadedFileCount();
	this->enterLevelIfDoneLoading();
}

void LoadingScreen::enterLevelIfDoneLoading()
{
	if (this->levelIsLoaded())
	{
		if (this->onLoadCallback != nullptr)
		{
			this->onLoadCallback(this->map);
		}
	}
}

void LoadingScreen::incrementLoadedFileCount()
{
	this->loadedFileCount.fetch_add(1);
	this->progressBar->setProgress(this->totalFileCount == 0 ? 0.0f : (float)this->loadedFileCount / (float)this->totalFileCount);
}

bool LoadingScreen::levelIsLoaded() 
{
	return this->loadedFileCount >= this->totalFileCount - 1;
}

bool LoadingScreen::isPreloadableImage(std::string filePath)
{
	if (StrUtils::endsWith(filePath, ".png", true) ||
		StrUtils::endsWith(filePath, ".jpg", true) ||
		StrUtils::endsWith(filePath, ".jpeg", true))
	{
		return true;
	}

	return false;
}

bool LoadingScreen::isPreloadableSound(std::string filePath)
{
	if (StrUtils::endsWith(filePath, ".mp3", true) ||
		StrUtils::endsWith(filePath, ".wav", true))
	{
		return true;
	}

	return false;
}
