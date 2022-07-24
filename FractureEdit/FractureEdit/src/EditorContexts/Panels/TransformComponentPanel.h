#pragma once
#ifndef TRANSFORMPANEL_H
#define TRANSFORMPANEL_H

#include "UIElement.h"

namespace Fracture
{
	struct TransformComponent;

	struct TransfromComponentPanel : UIElement
	{
		TransfromComponentPanel(TransformComponent* transform);
		void OnRender(bool* p_open);
		TransformComponent* component;

	};



}

#endif