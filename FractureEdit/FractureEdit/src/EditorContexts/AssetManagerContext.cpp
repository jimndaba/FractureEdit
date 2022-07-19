#include "EdPCH.h"
#include "AssetManagerContext.h"

Fracture::AssetManagerContext::AssetManagerContext()
{
}

void Fracture::AssetManagerContext::OnRender(bool* p_open)
{
	ImGui::Begin("Assets");
	ImGui::End();
}
