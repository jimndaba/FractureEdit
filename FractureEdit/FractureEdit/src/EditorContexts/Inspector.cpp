#include "EdPCH.h"
#include "Inspector.h"
#include "EditorApplication.h"
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
	if (EditorApplication::CurrentScene()->HasTagComponent(evnt->Entity))
	{
		mElements.push_back(std::make_shared<TagComponentPanel>(EditorApplication::CurrentScene()->GetTagComponent(evnt->Entity)));
	}

	if (EditorApplication::CurrentScene()->HasTransformComponent(evnt->Entity))
	{
		mElements.push_back(std::make_shared<TransfromComponentPanel>(EditorApplication::CurrentScene()->GetTransformComponent(evnt->Entity)));
	}	

	if (EditorApplication::CurrentScene()->HasCameraComponent(evnt->Entity))
	{
		mElements.push_back(std::make_shared<CameraComponentPanel>(EditorApplication::CurrentScene()->GetCameraComponent(evnt->Entity)));
	}

	if (EditorApplication::CurrentScene()->HasPointlightComponent(evnt->Entity))
	{
		mElements.push_back(std::make_shared<PointlightPanel>(EditorApplication::CurrentScene()->GetPointlightComponent(evnt->Entity)));
	}


	if (EditorApplication::CurrentScene()->HasStaticMeshComponent(evnt->Entity))
	{
		mElements.push_back(std::make_shared<StaticMeshComponentPanel>(EditorApplication::CurrentScene()->GetStaticMeshComponent(evnt->Entity)));
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
