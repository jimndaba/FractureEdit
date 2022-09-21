#include "EdPCH.h"
#include "Inspector.h"
#include "EditorApplication.h"
#include "scene/SceneManager.h"
#include "EditorContexts/Panels/InspectorPanels.h"

Fracture::Inspector::Inspector():EditingContext()
{
	
}

void Fracture::Inspector::OnUpdate()
{
	
}

void Fracture::Inspector::OnRender(bool* p_open, Device* device)
{
	ImGui::Begin("Inspector");
	for(const auto& element : mElements)
	{
		element->OnRender(p_open);
	}
	ImGui::End();
}

void Fracture::Inspector::OnSubmitEntityForEdit(const std::shared_ptr<SubmitEntityForEdit>& evnt)
{	
	if (EditorApplication::GetSceneManager()->HasTagComponent(evnt->Entity))
	{
		mElements.push_back(std::make_shared<TagComponentPanel>(EditorApplication::GetSceneManager()->GetTagComponent(evnt->Entity)));
	}

	if (EditorApplication::GetSceneManager()->HasTransformComponent(evnt->Entity))
	{
		mElements.push_back(std::make_shared<TransfromComponentPanel>(EditorApplication::GetSceneManager()->GetTransformComponent(evnt->Entity)));
	}	

	if (EditorApplication::GetSceneManager()->HasCameraComponent(evnt->Entity))
	{
		mElements.push_back(std::make_shared<CameraComponentPanel>(EditorApplication::GetSceneManager()->GetCameraComponent(evnt->Entity)));
	}

	if (EditorApplication::GetSceneManager()->HasPointlightComponent(evnt->Entity))
	{
		mElements.push_back(std::make_shared<PointlightPanel>(EditorApplication::GetSceneManager()->GetPointlightComponent(evnt->Entity)));
	}

	if (EditorApplication::GetSceneManager()->HasStaticMeshComponent(evnt->Entity))
	{
		mElements.push_back(std::make_shared<StaticMeshComponentPanel>(EditorApplication::GetSceneManager()->GetStaticMeshComponent(evnt->Entity)));
	}

	if (EditorApplication::GetSceneManager()->HasRigidBodyComponent(evnt->Entity))
	{
		mElements.push_back(std::make_shared<RigidbodyComponentPanel>(EditorApplication::GetSceneManager()->GetRigidBodyComponent(evnt->Entity)));
	}

	if (EditorApplication::GetSceneManager()->HasColliderComponent(evnt->Entity))
	{
		mElements.push_back(std::make_shared<ColliderComponentPanel>(EditorApplication::GetSceneManager()->GetColliderComponent(evnt->Entity)));
	}

	for (const auto& element : mElements)
	{
		element->OnAttach();
	}
}

void Fracture::Inspector::OnReleaseEntityFromEdit(const std::shared_ptr<ReleaseEntityFromEdit>& evnt)
{
	for (const auto& element : mElements)
	{
		element->OnDettach();
	}
	mElements.clear();
}
