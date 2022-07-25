#include "EdPCH.h"
#include "OptionsMenuPanel.h"
#include "Panels/EngineOptionsPanels.h"
#include "EditorContexts/Viewport.h"

Fracture::EngineOpitonsContext::EngineOpitonsContext()
{
}

void Fracture::EngineOpitonsContext::OnInit()
{
	{
		mCameraOptions = std::make_shared<CameraOptions>(Viewport::ViewportCamera());
	}
}

void Fracture::EngineOpitonsContext::OnUpdate()
{
}

void Fracture::EngineOpitonsContext::OnRender(bool* p_open, Device* device)
{
	ImGui::Begin("Engine Options",p_open);
	if (ImGui::TreeNodeEx("Camera Options"))
	{
		mCameraOptions->OnRender(p_open);
	}
	ImGui::End();
}
