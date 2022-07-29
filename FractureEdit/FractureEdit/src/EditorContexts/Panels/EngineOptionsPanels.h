#pragma once
#ifndef ENGINEOPTIONPANEL_H
#define ENGINEOPTIONPANEL_H

#include "UIElement.h"

namespace Fracture
{
	struct CameraComponent;
	struct FractureProject;

	struct ProjectOptions : public UIElement
	{
		ProjectOptions(FractureProject* p);
		void OnRender(bool* p_open);
		FractureProject* project;
	};

	struct CameraOptions : public UIElement
	{
		CameraOptions(CameraComponent* component);
		void OnRender(bool* p_open);
		CameraComponent* camera;
	};
}

#endif