#pragma once
#ifndef ACTION_H
#define ACTION_H


namespace Fracture
{
	struct Action
	{
		virtual void Do() = 0;
	};	
}


#endif