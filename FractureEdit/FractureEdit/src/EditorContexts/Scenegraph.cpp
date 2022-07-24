#include "EdPCH.h"
#include "Scenegraph.h"
#include "EditorApplication.h"

Fracture::ScenegraphView::ScenegraphView():EditingContext()
{
}

void Fracture::ScenegraphView::OnUpdate()
{
}

void Fracture::ScenegraphView::OnRender(bool* p_open, Device* device)
{
	ImGui::Begin("Scenegraph");
	ImGuiTableFlags flags = ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_BordersInnerV;

	ImGui::BeginTable("SceneGraphHeader",1, flags);

	ImGuiTableColumnFlags columnFlags = ImGuiTableColumnFlags_WidthFixed;
	ImGui::TableSetupColumn("Entity", columnFlags, 200);

	ImGui::TableHeadersRow();
	ImGui::TableNextRow();

	if (EditorApplication::CurrentScene())
	{
		DrawEntity(EditorApplication::CurrentScene()->RootEntity);
	}	

	ImGui::EndTable();

	if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered() && !ImGui::GetIO().KeyShift)
	{
		EditorApplication::Dispatcher()->Publish(std::make_shared<ReleaseEntityFromEdit>(Selection));
		Selection = UUID();
	}

	ImGui::End();
}

void Fracture::ScenegraphView::DrawEntity(const UUID& entity)
{
	const auto& tag = EditorApplication::CurrentScene()->GetTagComponent(entity);
	bool isSelected = false;
	ImGuiTreeNodeFlags flags;

	if (tag)
	{
		flags = ((Selection == entity) ? ImGuiTreeNodeFlags_Selected : isSelected) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_DefaultOpen;


		const auto& hierachy = EditorApplication::CurrentScene()->GetHierachyComponent(entity);

		if (hierachy->Children.empty())
		{
			flags |= ImGuiTreeNodeFlags_Leaf;
		}

		ImGui::TableNextColumn();
		bool opened = ImGui::TreeNodeEx(std::to_string((uint32_t)entity).c_str(), flags, tag->Name.c_str());
		if (ImGui::IsItemClicked())
		{
			EditorApplication::Dispatcher()->Publish(std::make_shared<SubmitEntityForEdit>(entity));
			Selection = entity;
		}
		ImGui::TableNextColumn();

		if (opened)
		{
			for (const auto& child : hierachy->Children)
			{
				DrawEntity(child);
			}
			ImGui::TreePop();
		}
	}
}
