#include "EdPCH.h"
#include "AssetManagerContext.h"

Fracture::AssetManagerContext::AssetManagerContext() : EditingContext()
{
}

void Fracture::AssetManagerContext::OnUpdate()
{
}

void Fracture::AssetManagerContext::OnRender(bool* p_open, Device* device)
{
	ImGui::Begin("Assets");
	ImGui::End();
}
