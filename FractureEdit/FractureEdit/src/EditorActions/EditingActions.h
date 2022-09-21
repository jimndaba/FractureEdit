#pragma once
#ifndef EDITINGACTIONS_H
#define EDITINGACTIONS_H

#include "Action.h"
#include "EditorApplication.h"



namespace Fracture
{
	struct SelectEntityAction : public Action
	{
		SelectEntityAction(const UUID& id);
		void Do();
		UUID entity;
	};

	//TODO
	struct TransformComponent;
	struct TagComponent;
	struct HierachyComponent;
	struct StaticMeshComponent;
	struct PointlightComponent;
	struct CameraComponent;
	struct RigidBodyComponent;
	struct ColliderComponent;

	struct DuplicateEntityAction : public Action
	{
		DuplicateEntityAction(const UUID& id);
		void Do();
		UUID old_entity;


		void CopyTransformIfExists(const UUID& from, const UUID& to);
		void CopyTagIfExists(const UUID& from, const UUID& to);
		void CopyHierachyIfExists(const UUID& from, const UUID& to);
		void CopyCameraIfExists(const UUID& from, const UUID& to);
		void CopyStaticMeshIfExists(const UUID& from, const UUID& to);
		void CopyPointlightIfExists(const UUID& from, const UUID& to);
		void CopyRigidBodyIfExists(const UUID& from, const UUID& to);
		void CopyColliderIfExists(const UUID& from, const UUID& to);

		std::shared_ptr<TransformComponent> Copy(UUID entity, TransformComponent* component);
		std::shared_ptr<TagComponent> Copy(UUID entity, TagComponent* component);
		std::shared_ptr<HierachyComponent> Copy(UUID entity, HierachyComponent* component);
		std::shared_ptr<StaticMeshComponent> Copy(UUID entity, StaticMeshComponent* component);
		std::shared_ptr<PointlightComponent> Copy(UUID entity, PointlightComponent* component);
		std::shared_ptr<CameraComponent> Copy(UUID entity, CameraComponent* component);
		std::shared_ptr<RigidBodyComponent> Copy(UUID entity, RigidBodyComponent* component);
		std::shared_ptr<ColliderComponent> Copy(UUID entity, ColliderComponent* component);
	};

	struct DeleteEntityAction : public Action
	{
		DeleteEntityAction(const UUID& id);
		void Do();
		UUID entity;
	};

	//TODO
	struct SetParentAction : public Action
	{
		SetParentAction(const UUID& e, const UUID& new_parent);
		UUID parent;
		UUID entity;
		void Do();
	};

	struct AddChildAction : public Action
	{
		AddChildAction(const UUID& p,const UUID& c);
		void Do();

		UUID parent;
		UUID child;
	};

	struct RemoveChildAction : public Action
	{
		RemoveChildAction(const UUID& p, const UUID& c);
		void Do();

		UUID parent;
		UUID child;
	};


}


#endif