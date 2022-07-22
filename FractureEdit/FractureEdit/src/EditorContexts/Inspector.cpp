#include "EdPCH.h"
#include "Inspector.h"

Fracture::Inspector::Inspector()
{
	mTranfoms = std::make_unique<TransfromComponentPanel>();
}

void Fracture::Inspector::OnUpdate()
{
}

void Fracture::Inspector::OnRender(bool* p_open, Device* device)
{
	ImGui::Begin("Inspector");

	mTranfoms->OnRender(p_open);

	ImGui::End();
}
