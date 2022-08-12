#include "EdPCH.h"
#include "Scenegraph.h"
#include "EditorApplication.h"

Fracture::ScenegraphView::ScenegraphView():EditingContext()
{
	mEntityIcon = AssetManager::GetTextureByName("EntityIcon");
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
	ImGui::TableSetupColumn("Scene", columnFlags, 200);

	ImGui::TableHeadersRow();
	ImGui::TableNextRow();

	if (EditorApplication::CurrentScene())
	{
		DrawEntity(EditorApplication::CurrentScene()->RootEntity);
	}	

	ImGui::EndTable();

	if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered() && !ImGui::GetIO().KeyShift)
	{
		ClearSelection();
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


		ImGui::Image((ImTextureID)mEntityIcon->RenderID, ImVec2 {8, 8 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::SameLine();


		bool opened = ImGui::TreeNodeEx(std::to_string((uint32_t)entity).c_str(), flags, tag->Name.c_str());
		if (ImGui::IsItemClicked())
		{
			ClearSelection();
			EditorApplication::ActionPlayer->Submit<SelectEntityAction>(entity);
		}

		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
		{
			const auto& position = EditorApplication::CurrentScene()->GetTransformComponent(entity)->Position;
			CameraSystem::LookAt(*Viewport::ViewportCamera(),position);
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

void Fracture::ScenegraphView::ClearSelection()
{
	EditorApplication::Dispatcher()->Publish(std::make_shared<ReleaseEntityFromEdit>(Selection));
	Selection = UUID();
}

void Fracture::ScenegraphView::OnReleaseEntityFromEdit(const std::shared_ptr<ReleaseEntityFromEdit>& evnt)
{
	Selection = UUID();
}

void Fracture::ScenegraphView::OnSubmitEntityForEdit(const std::shared_ptr<SubmitEntityForEdit>& evnt)
{
	Selection = evnt->Entity;
}
