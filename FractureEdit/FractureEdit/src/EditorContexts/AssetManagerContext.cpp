#include "EdPCH.h"
#include "AssetManagerContext.h"

Fracture::AssetManagerContext::AssetManagerContext()
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
