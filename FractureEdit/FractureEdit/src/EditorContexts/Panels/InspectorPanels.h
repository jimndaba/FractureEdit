#pragma once
#ifndef TRANSFORMPANEL_H
#define TRANSFORMPANEL_H

#include "UIElement.h"

namespace Fracture
{
	struct TransformComponent;
	struct TagComponent;
	struct PointlightComponent;
	struct CameraComponent;
	struct StaticMeshComponent;


	struct TransfromComponentPanel :public UIElement
	{
		TransfromComponentPanel(TransformComponent* transform);
		void OnRender(bool* p_open);
		TransformComponent* component;

	};

	struct TagComponentPanel :public UIElement
	{
		TagComponentPanel(TagComponent* tag);
		void OnRender(bool* p_open);
		TagComponent* component;
	};

	struct PointlightPanel : public UIElement
	{
		PointlightPanel(PointlightComponent* light);
		void OnRender(bool* p_open);
		PointlightComponent* component;
	};

	struct CameraComonentPanel : public UIElement
	{
		CameraComonentPanel(CameraComponent* light);
		void OnRender(bool* p_open);
		CameraComponent* component;
	};


}

#endif