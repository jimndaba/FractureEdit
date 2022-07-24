#include "EdPCH.h"
#include "TransformComponentPanel.h"
#include "core/Components.h"

Fracture::TransfromComponentPanel::TransfromComponentPanel(TransformComponent* transform):
	component(transform)
{
}

void Fracture::TransfromComponentPanel::OnRender(bool* p_open)
{
	float button_size = 100;
	ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_DefaultOpen;

	bool open = ImGui::TreeNodeEx("Transform", tree_flags);

	if (open)
	{
		ImGuiTableFlags flags = ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersH;

		ImGui::BeginTable("TransformComps", 4, flags);
		Property("Position", component->Position);
		Property("Scale", component->Scale);
		Property("Rotation ", component->Rotation);
		ImGui::EndTable();

		ImGui::TreePop();
	}

}
