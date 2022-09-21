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
	struct RigidBodyComponent;
	struct ColliderComponent;

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

	struct CameraComponentPanel : public UIElement
	{
		CameraComponentPanel(CameraComponent* light);
		void OnRender(bool* p_open);
		CameraComponent* component;
	};

	struct StaticMeshComponentPanel : public UIElement
	{
		StaticMeshComponentPanel(StaticMeshComponent* mesh);
		void OnAttach();
		void OnRender(bool* p_open);
		StaticMeshComponent* component;
		uint32_t blank_texture;
	};

	struct RigidbodyComponentPanel : public UIElement
	{
		RigidbodyComponentPanel(RigidBodyComponent* rigidbody);
		void OnAttach();
		void OnRender(bool* p_open);
		RigidBodyComponent* component;
	};

	struct ColliderComponentPanel : public UIElement
	{
		ColliderComponentPanel(ColliderComponent* rigidbody);
		void OnAttach();
		void OnRender(bool* p_open);
		ColliderComponent* component;
	};

}

#endif