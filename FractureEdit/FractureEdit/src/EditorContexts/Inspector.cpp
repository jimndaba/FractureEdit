#include "EdPCH.h"
#include "Inspector.h"
#include "EditorApplication.h"

Fracture::Inspector::Inspector():EditingContext()
{
	
}

void Fracture::Inspector::OnUpdate()
{
	
}

void Fracture::Inspector::OnRender(bool* p_open, Device* device)
{
	ImGui::Begin("Inspector");

	if (mTranfomWidget)
	{
		mTranfomWidget->OnRender(p_open);
	}

	ImGui::End();
}

void Fracture::Inspector::OnSubmitEntityForEdit(const std::shared_ptr<SubmitEntityForEdit>& evnt)
{
	if (mTranfomWidget)
	{
		mTranfomWidget.reset();
	}
	if (EditorApplication::CurrentScene()->HasTransformComponent(evnt->Entity))
	{
		mTranfomWidget = std::make_unique<TransfromComponentPanel>(EditorApplication::CurrentScene()->GetTransformComponent(evnt->Entity));
	}	
}

void Fracture::Inspector::OnReleaseEntityFromEdit(const std::shared_ptr<ReleaseEntityFromEdit>& evnt)
{
	if (mTranfomWidget)
	{
		mTranfomWidget.reset();
	}
}
