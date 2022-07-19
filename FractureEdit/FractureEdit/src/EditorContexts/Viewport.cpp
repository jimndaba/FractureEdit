#include "EdPCH.h"
#include "Viewport.h"

Fracture::Viewport::Viewport()
{
}

void Fracture::Viewport::OnRender(bool* p_open)
{
	ImGui::Begin("Viewport");
	ImGui::End();
}
