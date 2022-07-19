#include "EdPCH.h"
#include "TransformComponentPanel.h"
#include <imgui/imgui_internal.h>

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

		ImGuiTableColumnFlags columnFlags = ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_IndentEnable;
		ImGui::TableNextColumn();
		ImGui::TableNextColumn();

		ImGui::Button("X", ImVec2{ 25, 25 });
		ImGui::TableNextColumn();
		ImGui::Button("Y", ImVec2{ 25, 25 });
		ImGui::TableNextColumn();
		ImGui::Button("Z", ImVec2{ 25, 25 });	

		ImGui::TableNextRow();

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

bool Fracture::TransfromComponentPanel::Property(const std::string& label, glm::vec3& value, float reset_value)
{
	ImGui::TableNextColumn();

	ImGui::Text(label.c_str());

	ImGui::TableNextColumn();
	{
	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 1.5f;
	ImVec2 buttonSize = { lineHeight + 2.0f, lineHeight };
	if (ImGui::Button("-", buttonSize))
	{
		value.x = reset_value;
	}

	ImGui::SameLine();
	ImGui::PushItemWidth(-5);
	ImGui::DragFloat("##posx", &value.x, 0.01f, 0.0f, 100.0f, "%.2f");
	}
	ImGui::TableNextColumn();
	{
		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 1.5f;
		ImVec2 buttonSize = { lineHeight + 2.0f, lineHeight };
		if (ImGui::Button("-", buttonSize))
		{
			value.y = reset_value;
		}

		ImGui::SameLine();
		ImGui::PushItemWidth(-5);
		ImGui::DragFloat("##posy", &value.y, 0.01f, 0.0f, 100.0f, "%.2f");

	}
	ImGui::TableNextColumn();
	{
		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 1.5f;
		ImVec2 buttonSize = { lineHeight + 2.0f, lineHeight };
		if (ImGui::Button("-", buttonSize))
		{
			value.z = reset_value;
		}

		ImGui::SameLine();
		ImGui::PushItemWidth(-5);
		ImGui::DragFloat("##posz", &value.z, 0.01f, 0.0f, 100.0f, "%.2f");
	}
	return false;


}
