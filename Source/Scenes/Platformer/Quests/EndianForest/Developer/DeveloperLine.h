#pragma once

#include "Engine/Quests/QuestLine.h"

class GameObject;

class DeveloperLine : public QuestLine
{
public:
	static DeveloperLine* create();
	QuestTask* deserialize(GameObject* owner, std::string questTask, std::string questTag) override;

	static const std::string MapKeyQuestLine;
	static const std::map<std::string, std::tuple<bool, std::function<QuestTask*(GameObject*, std::string, std::string)>>> Quests;

private:
	typedef QuestLine super;
};


