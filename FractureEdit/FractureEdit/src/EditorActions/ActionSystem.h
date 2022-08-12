#pragma once
#ifndef ACTIONSYSTEM_H
#define ACTIONSYSTEM_H

#include "EditingActions.h"

namespace Fracture
{
	

	class ActionSystem
	{

	public:
		ActionSystem();

		void Do();

		template<class T, typename... Args>
		static void Submit(Args&&... params);

		static std::queue<std::shared_ptr<Action>> Actions;
	};




	template<class T, typename ...Args>
	inline void ActionSystem::Submit(Args && ...params)
	{
		auto action = std::make_shared<T>(params...);
		Actions.push(action);
	}

}


#endif