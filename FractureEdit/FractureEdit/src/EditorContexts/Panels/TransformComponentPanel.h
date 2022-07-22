#pragma once
#ifndef TRANSFORMPANEL_H
#define TRANSFORMPANEL_H

#include "UIElement.h"

namespace Fracture
{
	struct TransfromComponentPanel : UIElement
	{
		TransfromComponentPanel();
		void OnRender(bool* p_open);
		//TransformComponent* component;

		

	};



}

#endif