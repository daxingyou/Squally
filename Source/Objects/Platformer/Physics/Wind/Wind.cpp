#include "Wind.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"
#include "cocos/2d/CCParticleSystemQuad.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/Physics/Wind/WindGenericPreview.h"
#include "Objects/Platformer/Physics/Wind/WindSetSpeedPreview.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

#include "Strings/Hacking/Objects/Wind/SetWindSpeed/RegisterEax.h"
#include "Strings/Hacking/Objects/Wind/SetWindSpeed/RegisterEbx.h"
#include "Strings/Hacking/Objects/Wind/SetWindSpeed/SetWindSpeed.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_WIND_SPEED 1

const std::string Wind::MapKeyWind = "wind";
const float Wind::BaseWindSpeed = 1024.0f;

Wind* Wind::create(ValueMap& initProperties)
{
	Wind* instance = new Wind(initProperties);

	instance->autorelease();

	return instance;
}

Wind::Wind(ValueMap& initProperties) : HackableObject(initProperties)
{
	float speedX = 0.0f;
	float speedY = 0.0f;

	if (GameUtils::keyExists(this->properties, "speed-x"))
	{
		speedX = this->properties.at("speed-x").asFloat();
	}

	if (GameUtils::keyExists(this->properties, "speed-y"))
	{
		speedY = this->properties.at("speed-y").asFloat();
	}

	this->windSize = Size(this->properties.at(SerializableObject::MapKeyWidth).asFloat(), this->properties.at(SerializableObject::MapKeyHeight).asFloat());
	this->windSpeedDefault = Vec2(speedX, speedY);
	this->windSpeed = this->windSpeedDefault;
	this->windParticles = ParticleSystemQuad::create(ParticleResources::Gust);
	this->windForce = CollisionObject::create(PhysicsBody::createBox(this->windSize), (CollisionType)PlatformerCollisionType::Force, false, false);

	this->windParticles->setAnchorPoint(Vec2::ZERO);
	this->windParticles->setPositionType(ParticleSystem::PositionType::GROUPED);

	this->addChild(this->windForce);
	this->addChild(this->windParticles);
}

Wind::~Wind()
{
}

void Wind::onEnter()
{
	super::onEnter();

	this->windParticles->setTotalParticles(int(this->windSize.width * this->windSize.height / 4096.0f));
	this->windParticles->setPosVar(Vec2(this->windSize.width / 2.0f, this->windSize.height / 2.0f));

	this->scheduleUpdate();
}

void Wind::initializePositions()
{
	super::initializePositions();
}

void Wind::initializeListeners()
{
	super::initializeListeners();

	this->windForce->setContactUpdateCallback(CC_CALLBACK_2(Wind::applyWindForce, this));

	this->windForce->whenCollidesWith({ (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{
		// Speed is applied in the update applyWindForce

		return CollisionObject::CollisionResult::DoNothing;
	});
}

void Wind::update(float dt)
{
	super::update(dt);

	this->updateWind(dt);
}

void Wind::applyWindForce(std::set<CollisionObject*>* targets, float dt)
{
	for (auto it = targets->begin(); it != targets->end(); it++)
	{
		(*it)->setVelocity((*it)->getVelocity() + this->windSpeed * Wind::BaseWindSpeed * dt);
	}
}

Vec2 Wind::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void Wind::registerHackables()
{
	super::registerHackables();

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_WIND_SPEED,
			HackableCode::LateBindData(
				Wind::MapKeyWind,
				Strings::Hacking_Objects_Wind_SetWindSpeed_SetWindSpeed::create(),
				UIResources::Menus_Icons_Spell,
				WindSetSpeedPreview::create(),
				{
					{ HackableCode::Register::zax, Strings::Hacking_Objects_Wind_SetWindSpeed_RegisterEax::create() },
					{ HackableCode::Register::zbx, Strings::Hacking_Objects_Wind_SetWindSpeed_RegisterEbx::create() },
				},
				5.0f
			)
		},
	};

	auto updateWindFunc = &Wind::updateWind;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)updateWindFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

HackablePreview* Wind::createDefaultPreview()
{
	return WindGenericPreview::create();
}

void Wind::updateWind(float dt)
{
	this->windSpeed = this->windSpeedDefault;

	static volatile float* xSpeedPtr;
	static volatile float* ySpeedPtr;

	xSpeedPtr = &this->windSpeed.x;
	ySpeedPtr = &this->windSpeed.y;

	ASM(push EAX);
	ASM(push EBX);

	ASM_MOV_REG_VAR(EAX, xSpeedPtr);
	ASM_MOV_REG_VAR(EBX, ySpeedPtr);

	ASM(fld dword ptr [EBX])
	ASM(fld dword ptr [EAX])

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_WIND_SPEED);
	ASM(fstp dword ptr [EAX])
	ASM(fstp dword ptr [EBX])
	ASM_NOP16()
	ASM_NOP16()
	HACKABLE_CODE_END();

	ASM(pop EBX);
	ASM(pop EAX);

	HACKABLES_STOP_SEARCH();

	if (this->windSpeed.x == 0.0f && this->windSpeed.y == 0.0f)
	{
		this->windParticles->stopSystem();
	}
	else
	{
		if (!this->windParticles->isActive())
		{
			this->windParticles->start();
		}
	}

	static volatile float angle;

	angle = std::atan2(this->windSpeed.y, this->windSpeed.x) * 180.0f / float(M_PI);

	this->windParticles->setAngle(angle);
}