#include "EdPCH.h"
#include "Scenegraph.h"

Fracture::ScenegraphView::ScenegraphView()
{
}

void Fracture::ScenegraphView::OnRender(bool* p_open)
{
	ImGui::Begin("Scenegraph");
	ImGuiTableFlags flags = ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_BordersInnerV;

	ImGui::BeginTable("SceneGraphHeader",1, flags);

	ImGuiTableColumnFlags columnFlags = ImGuiTableColumnFlags_WidthFixed;
	ImGui::TableSetupColumn("Entity", columnFlags, 200);

	ImGui::TableHeadersRow();
	ImGui::TableNextRow();
	
	for (int i = 0; i < 10; i++)
	{
		ImGui::TableNextColumn();
		ImGui::TreeNodeEx("GameObject", flags);
		ImGui::TableNextColumn();
	}

	ImGui::EndTable();
	ImGui::End();
}
