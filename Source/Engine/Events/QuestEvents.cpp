#include "QuestEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string QuestEvents::EventAdvanceNextQuestTask = "EVENT_ADVANCE_NEXT_QUEST_TASK";

void QuestEvents::TriggerAdvanceToNextQuestTask(AdvanceNextQuestArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		QuestEvents::EventAdvanceNextQuestTask,
		&args
	);
}