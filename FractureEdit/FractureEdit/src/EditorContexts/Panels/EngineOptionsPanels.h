#pragma once
#ifndef ENGINEOPTIONPANEL_H
#define ENGINEOPTIONPANEL_H

#include "UIElement.h"

namespace Fracture
{
	struct CameraComponent;

	struct CameraOptions : public UIElement
	{
		CameraOptions(CameraComponent* component);
		void OnRender(bool* p_open);
		CameraComponent* camera;
	};
}

#endif