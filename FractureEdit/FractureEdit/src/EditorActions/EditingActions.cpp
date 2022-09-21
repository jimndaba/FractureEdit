#include "EdPCH.h"
#include "EditingActions.h"

//#include "events/Eventbus.h"
#include "scene/SceneManager.h"
#include "ActionSystem.h"


Fracture::SelectEntityAction::SelectEntityAction(const UUID& id) : entity(id)
{
}
void Fracture::SelectEntityAction::Do()
{
	EditorApplication::Dispatcher()->Publish(std::make_shared<SubmitEntityForEdit>(entity));
}

#pragma region Duplicate
Fracture::DuplicateEntityAction::DuplicateEntityAction(const UUID& id): old_entity(id)
{
	
}

void Fracture::DuplicateEntityAction::Do()
{
	auto new_entity = EditorApplication::GetSceneManager()->AddEntity();

	CopyTagIfExists(old_entity, new_entity);
	CopyTransformIfExists(old_entity, new_entity);	
	CopyStaticMeshIfExists(old_entity, new_entity);
	CopyPointlightIfExists(old_entity, new_entity);
	CopyCameraIfExists(old_entity, new_entity);
	CopyHierachyIfExists(old_entity, new_entity);

	

	if (EditorApplication::GetSceneManager()->HasHierachyComponent(old_entity))
	{
		auto hierachy = EditorApplication::GetSceneManager()->GetHierachyComponent(old_entity);
	
		for (const auto& child : hierachy->Children)
		{
			//ActionSystem::Submit<DuplicateEntityAction>(child,m);
			//ActionSystem::Submit<SetParentAction>(m, out_entity);
		}
	}


	EditorApplication::Dispatcher()->Publish(std::make_shared<ReleaseEntityFromEdit>(UUID()));
	ActionSystem::Submit<SelectEntityAction>(new_entity);


}

void Fracture::DuplicateEntityAction::CopyTransformIfExists(const UUID& from, const UUID& to)
{	
	if (EditorApplication::GetSceneManager()->HasTransformComponent(from))
	{
		const auto& comp = EditorApplication::GetSceneManager()->GetTransformComponent(from);
		EditorApplication::GetSceneManager()->AddComponent(to, Copy(to, comp));
	}
}

void Fracture::DuplicateEntityAction::CopyTagIfExists(const UUID& from, const UUID& to)
{
	if (EditorApplication::GetSceneManager()->HasTagComponent(from))
	{
		const auto& comp = EditorApplication::GetSceneManager()->GetTagComponent(from);
		auto tag = Copy(to, comp);
		EditorApplication::GetSceneManager()->AddComponent(to,tag);
	}
}

void Fracture::DuplicateEntityAction::CopyHierachyIfExists(const UUID& from, const UUID& to)
{	
	if (EditorApplication::GetSceneManager()->HasHierachyComponent(from))
	{
		const auto& comp = EditorApplication::GetSceneManager()->GetHierachyComponent(from);
		ActionSystem::Submit<AddChildAction>(comp->Parent, to);
		EditorApplication::GetSceneManager()->AddComponent(to, Copy(to, comp));
	}
}

void Fracture::DuplicateEntityAction::CopyCameraIfExists(const UUID& from, const UUID& to)
{	
	if (EditorApplication::GetSceneManager()->HasCameraComponent(from))
	{
		const auto& comp = EditorApplication::GetSceneManager()->GetCameraComponent(from);
		EditorApplication::GetSceneManager()->AddComponent(to, Copy(to, comp));
	}
}

void Fracture::DuplicateEntityAction::CopyStaticMeshIfExists(const UUID& from, const UUID& to)
{	
	if (EditorApplication::GetSceneManager()->HasStaticMeshComponent(from))
	{
		const auto& comp = EditorApplication::GetSceneManager()->GetStaticMeshComponent(from);
		EditorApplication::GetSceneManager()->AddComponent(to, Copy(to, comp));
	}
}

void Fracture::DuplicateEntityAction::CopyPointlightIfExists(const UUID& from, const UUID& to)
{	
	if (EditorApplication::GetSceneManager()->HasPointlightComponent(from))
	{
		const auto& comp = EditorApplication::GetSceneManager()->GetPointlightComponent(from);
		EditorApplication::GetSceneManager()->AddComponent(to, Copy(to, comp));
	}
}

void Fracture::DuplicateEntityAction::CopyRigidBodyIfExists(const UUID& from, const UUID& to)
{
	if (EditorApplication::GetSceneManager()->HasRigidBodyComponent(from))
	{
		const auto& comp = EditorApplication::GetSceneManager()->GetRigidBodyComponent(from);
		EditorApplication::GetSceneManager()->AddComponent(to, Copy(to, comp));
	}
}

void Fracture::DuplicateEntityAction::CopyColliderIfExists(const UUID& from, const UUID& to)
{
	if (EditorApplication::GetSceneManager()->HasColliderComponent(from))
	{
		//const auto& comp = EditorApplication::GetSceneManager()->GetColliderComponent(from);
		//EditorApplication::GetSceneManager()->AddComponent(to, Copy(to, comp));
	}
}

std::shared_ptr<Fracture::TransformComponent> Fracture::DuplicateEntityAction::Copy(UUID entity, TransformComponent* component)
{	
	auto transform = std::make_shared<TransformComponent>(
		entity,
		component->Position,
		component->Scale,
		component->Rotation
		);
	return transform;
}

std::shared_ptr<Fracture::TagComponent> Fracture::DuplicateEntityAction::Copy(UUID entity, TagComponent* component)
{
	auto tag = std::make_shared<TagComponent>(component->Name, entity);
	tag->Name = component->Name;
	tag->ID = entity;
	
	return tag;
}

std::shared_ptr<Fracture::HierachyComponent> Fracture::DuplicateEntityAction::Copy(UUID entity, HierachyComponent* component)
{
	HierachyParams p;
	p.HasParent = component->HasParent;
	p.Parent = component->Parent;
	return std::make_shared<HierachyComponent>(entity, p);
}

std::shared_ptr<Fracture::StaticMeshComponent> Fracture::DuplicateEntityAction::Copy(UUID entity, StaticMeshComponent* component)
{
	auto staticmesh = std::make_shared<StaticMeshComponent>(
		component->MeshName,
		component->Mesh,
		entity		
		);

	staticmesh->MaterialID = component->MaterialID;
	staticmesh->OverrideMeshMaterial = component->OverrideMeshMaterial;
	staticmesh->MeshID = component->MeshID;
	return staticmesh;
}

std::shared_ptr<Fracture::PointlightComponent> Fracture::DuplicateEntityAction::Copy(UUID entity, PointlightComponent* component)
{
	PointlightParams p;
	p.Compression = component->Compression;
	p.Diffuse = component->Diffuse;
	p.Intensity = component->Intensity;
	p.Radius = component->Radius;
	p.Specular = component->Specular;
	auto pointlight = std::make_shared<PointlightComponent>(entity, p);
	return pointlight;
}

std::shared_ptr<Fracture::CameraComponent> Fracture::DuplicateEntityAction::Copy(UUID entity, CameraComponent* component)
{
	CameraComponentParams p;
	p.Damping = component->Damping;
	p.Far = component->Far;
	p.FocalLength = component->FocalLength;
	p.FocalRange = component->FocalRange;
	p.FoV = component->FoV;
	p.Front = component->Front;
	p.Height = component->Height;
	p.Width = component->Width;
	p.Yaw = component->Yaw;
	p.Pitch = component->Pitch;
	p.Roll = component->Roll;
	p.Position = component->Position;
	p.Near = component->Near;
	p.Speed = component->Speed;
	p.Sensitivity = component->Sensitivity;
	p.Up = component->Up;
	auto camera = std::make_shared<CameraComponent>(entity, p);
	return camera;
}
std::shared_ptr<Fracture::RigidBodyComponent> Fracture::DuplicateEntityAction::Copy(UUID entity, RigidBodyComponent* component)
{
	std::shared_ptr<RigidBodyComponent> c = std::make_shared<RigidBodyComponent>(entity);
	c->AngularDrag = component->AngularDrag;
	return c;
}
std::shared_ptr<Fracture::ColliderComponent> Fracture::DuplicateEntityAction::Copy(UUID entity, ColliderComponent* component)
{
	std::shared_ptr<ColliderComponent> c = std::make_shared<ColliderComponent>(entity);
	//ToDo
	return c;
}
#pragma endregion

#pragma region DeleteAction
Fracture::DeleteEntityAction::DeleteEntityAction(const UUID& id):entity(id)
{
}
void Fracture::DeleteEntityAction::Do()
{
	EditorApplication::GetSceneManager()->RemoveEntityComponents(entity);
	EditorApplication::GetSceneManager()->RemoveEntity(entity);
	EditorApplication::Dispatcher()->Publish(std::make_shared<ReleaseEntityFromEdit>(UUID()));
}
#pragma endregion

Fracture::SetParentAction::SetParentAction(const UUID& e, const UUID& new_parent):entity(e),parent(new_parent)
{
}

void Fracture::SetParentAction::Do()
{
	if (EditorApplication::GetSceneManager()->HasHierachyComponent(entity))
	{
		const auto& hierachy = EditorApplication::GetSceneManager()->GetHierachyComponent(entity);

		if (hierachy->HasParent)
		{
			ActionSystem::Submit<RemoveChildAction>(hierachy->Parent, entity);
		}

		hierachy->HasParent = true;
		hierachy->Parent = parent;

		ActionSystem::Submit<AddChildAction>(parent, entity);
	}
}

Fracture::AddChildAction::AddChildAction(const UUID& p,const UUID& c):
	parent(p),
	child(c)
{	
}

void Fracture::AddChildAction::Do()
{
	if (Application::GetSceneManager()->HasHierachyComponent(parent))
	{		
		const auto& hierachy = Application::GetSceneManager()->GetHierachyComponent(parent);
		hierachy->Children.push_back(child);
	}
}

Fracture::RemoveChildAction::RemoveChildAction(const UUID& p, const UUID& c)
{
}

void Fracture::RemoveChildAction::Do()
{
	if (Application::GetSceneManager()->HasHierachyComponent(parent))
	{
		const auto& hierachy = Application::GetSceneManager()->GetHierachyComponent(parent);
		for (auto iter = hierachy->Children.begin(); iter != hierachy->Children.end(); ++iter)
		{
			if (*iter == child)
			{
				hierachy->Children.erase(iter);
				break;
			}
		}		
	}
}
