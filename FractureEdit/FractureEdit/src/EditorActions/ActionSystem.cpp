#include "EdPCH.h"
#include "ActionSystem.h"

std::queue<std::shared_ptr<Fracture::Action>> Fracture::ActionSystem::Actions;

Fracture::ActionSystem::ActionSystem()
{
}

void Fracture::ActionSystem::Do()
{
	while (!Actions.empty())
	{
		const auto& action = Actions.front();
		action->Do();
		Actions.pop();
	}
}
