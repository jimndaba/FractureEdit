#pragma once
#ifndef VIEWPORT_H
#define VIEWPORT_H


#include "EditingContext.h"

namespace Fracture
{
	class Viewport : public EditingContext
	{
	public:
		Viewport();

		void OnRender(bool* p_open);

	
	};
}


#endif