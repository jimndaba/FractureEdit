#pragma once
#ifndef ENGINEOPTIONPANEL_H
#define ENGINEOPTIONPANEL_H

#include "UIElement.h"
#include "Project/FractureProject.h"

namespace Fracture
{
	struct CameraComponent;
	struct FractureProject;
	class EditorApplication;

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

	struct NewSceneOptions : public UIElement
	{
		NewSceneOptions();
		void OnRender(bool* p_open);
	
	};

	struct NewProjectOptions : public UIElement
	{
		NewProjectOptions(EditorApplication& application);
		void OnRender(bool* p_open);
		EditorApplication& app;
		ProjectParams params;
	};
}

#endif