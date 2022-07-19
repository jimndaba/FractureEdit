#pragma once
#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H


#include "EditingContext.h"

namespace Fracture
{
	class ScenegraphView : public EditingContext
	{
	public:
		ScenegraphView();

		void OnRender(bool* p_open);

	};
}


#endif