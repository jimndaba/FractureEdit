#include "EdPCH.h"
#include "UIElement.h"
#include <imgui/imgui_internal.h>

bool Fracture::UIElement::Property(const std::string& label, glm::vec3& value, float reset_value)
{
	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 1.5f;
	ImVec2 buttonSize = { lineHeight + 0.0f, lineHeight };


	ImGui::TableNextColumn();

	ImGui::Text(label.c_str());

	ImGui::TableNextColumn();
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 0,0 });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.8f,0.30f,0.30f,1.0f });
		if (ImGui::Button("X", buttonSize))
		{
			value.x = reset_value;
		}
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
		ImGui::SameLine();
		ImGui::PushItemWidth(-5);
		ImGui::DragFloat("##posx", &value.x, 0.01f, 0.0f, 100.0f, "%.2f");
	}
	ImGui::TableNextColumn();
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 0,0 });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.30f,0.8f,0.30f,1.0f });
		if (ImGui::Button("Y", buttonSize))
		{
			value.y = reset_value;
		}

		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
		ImGui::SameLine();
		ImGui::PushItemWidth(-5);
		ImGui::DragFloat("##posy", &value.y, 0.01f, 0.0f, 100.0f, "%.2f");

	}
	ImGui::TableNextColumn();
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 0,0 });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.30f,0.30f,0.8f,1.0f });
		if (ImGui::Button("Z", buttonSize))
		{
			value.z = reset_value;
		}
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();

		ImGui::SameLine();
		ImGui::PushItemWidth(-5);
		ImGui::DragFloat("##posz", &value.z, 0.01f, 0.0f, 100.0f, "%.2f");
	}
	return false;

}
