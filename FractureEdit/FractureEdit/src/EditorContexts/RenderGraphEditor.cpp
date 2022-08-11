#include "EdPCH.h"
#include "RenderGraphEditor.h"
#include "../EditorApplication.h"
#include "events/Eventbus.h"

Fracture::RenderGraphEditor::RenderGraphEditor()
{

}

void Fracture::RenderGraphEditor::OnInit()
{
	mSceneView = std::make_unique<Viewport>("Rendered View");
	mSceneView->OnInit();

	mSaveIcon = AssetManager::GetTextureByName("SaveIcon");
	mOpenIcon = AssetManager::GetTextureByName("OpenIcon");

	mInspector = std::make_unique<RenderGraphInspector>();
	
}

void Fracture::RenderGraphEditor::OnUpdate()
{
	mSceneView->OnUpdate();
}

void Fracture::RenderGraphEditor::OnLoad()
{
	mSceneView->OnLoad();
}

void Fracture::RenderGraphEditor::OnRender(bool* p_open, Device* device)
{
	if (mCurrenScene)
	{
		//ImGui::Begin("DockSpace Demo", p_open);
		ImGuiIO& io = ImGui::GetIO();

		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id);
		}

		RenderToolbar();		
		if (_ShowViewport)
		{
			mSceneView->OnRender(&_ShowViewport, device);
		}

		if (_ShowInspector)
		{
			mInspector->OnRender(&_ShowInspector, device);
		}
	}
}

void Fracture::RenderGraphEditor::RenderToolbar()
{
	ImVec2 button_size = { 14,14 };

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4 , 4 });
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4, 1));
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));



	ImGui::Begin("##Toolbar1");
	ImGui::SameLine();
	if (ImGui::ImageButton((ImTextureID)mOpenIcon->RenderID, button_size, ImVec2 { 0, 1 }, ImVec2{ 1, 0 }))
	{
		EditorApplication::OpenScene();
	}
	ImGui::SameLine();
	if (ImGui::ImageButton((ImTextureID)mSaveIcon->RenderID, button_size, ImVec2 { 0, 1 }, ImVec2{ 1, 0 }))
	{
		EditorApplication::SaveScene();
	}
	ImGui::SameLine();
	ImGui::Button("Z", button_size);
	ImGui::SameLine();
	ImGui::Button("W", button_size);
	ImGui::End();

	ImGui::PopStyleVar(2);
	ImGui::PopStyleColor();
}

void Fracture::RenderGraphEditor::OnSetScene(const std::shared_ptr<SetSceneForEditing>& evnt)
{
	mCurrenScene = &evnt->scene;	
}

void Fracture::RenderGraphEditor::OnSetRenderGraph(const std::shared_ptr<SetRenderGraph>& evnt)
{
	mGraph = &evnt->Graph;
}

void Fracture::RenderGraphEditor::OnSubmitEntityForEdit(const std::shared_ptr<SubmitEntityForEdit>& evnt)
{
}

void Fracture::RenderGraphEditor::OnReleaseEntityFromEdit(const std::shared_ptr<ReleaseEntityFromEdit>& evnt)
{
}
