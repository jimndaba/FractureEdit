#include "EdPCH.h"
#include "TransformComponentPanel.h"


Fracture::TransfromComponentPanel::TransfromComponentPanel()
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

		glm::vec3 pos;
		glm::vec3 sc;
		glm::vec3 rot;

		Property("Position", pos);
		Property("Scale", sc);
		Property("Rotation ",rot);

		ImGui::EndTable();

		ImGui::TreePop();
	}

}
