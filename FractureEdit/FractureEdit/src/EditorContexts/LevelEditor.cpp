#include "EdPCH.h"
#include "LevelEditor.h"
#include "../EditorApplication.h"
#include "events/Eventbus.h"

Fracture::LevelEditor::LevelEditor() : EditingContext()
{
	currentTime = (float)glfwGetTime();
}

void Fracture::LevelEditor::OnInit()
{
	mSceneGraph = std::make_unique<ScenegraphView>();
	mInspector = std::make_unique<Inspector>();
	mSceneView = std::make_unique<Viewport>("Viewport");
	mAssets = std::make_unique<AssetManagerContext>();

	mSceneView->OnInit();	
	
	mSaveIcon = AssetManager::GetTextureByName("SaveIcon");
	mOpenIcon = AssetManager::GetTextureByName("OpenIcon");

}

void Fracture::LevelEditor::OnUpdate()
{
	mSceneView->OnUpdate();
}

void Fracture::LevelEditor::OnLoad()
{
	mSceneView->OnLoad();
}

void Fracture::LevelEditor::OnRender(bool* p_open, Device* device)
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
		if (_ShowScenegraph)
		{
			mSceneGraph->OnRender(&_ShowScenegraph, device);
		}
		if (_ShowInspector)
		{
			mInspector->OnRender(&_ShowInspector, device);
		}
		if (_ShowViewport)
		{
			mSceneView->OnRender(&_ShowViewport, device);
		}
		if (_ShowAssetManager)
		{
			mAssets->OnRender(&_ShowAssetManager, device);
		}

	}

}

void Fracture::LevelEditor::RenderToolbar()
{
	ImVec2 button_size = {14,14 };

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4 , 4});
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4, 1));
	ImGui::PushStyleColor(ImGuiCol_Button,ImVec4(0.0f, 0.0f, 0.0f, 0.0f));

	ImGui::Begin("##Toolbar");
	ImGui::SameLine();
	if (ImGui::ImageButton((ImTextureID)mOpenIcon->RenderID, button_size, ImVec2 { 0, 1 }, ImVec2{ 1, 0 }))
	{
		EditorApplication::OpenScene();
	}
	ImGui::SameLine();
	if (ImGui::ImageButton((ImTextureID)mSaveIcon->RenderID, button_size, ImVec2{ 0, 1 }, ImVec2{ 1, 0 }))
	{
		EditorApplication::SaveScene();
	}	

	ImGui::End();
	ImGui::PopStyleVar(2);
	ImGui::PopStyleColor();

}


void Fracture::LevelEditor::OnSetScene(const std::shared_ptr<SetSceneForEditing>& evnt)
{
	mCurrenScene = &evnt->scene;
}

void Fracture::LevelEditor::OnSetRenderGraph(const std::shared_ptr<SetRenderGraph>& evnt)
{
	mGraph = &evnt->Graph;
}

void Fracture::LevelEditor::OnSubmitEntityForEdit(const std::shared_ptr<SubmitEntityForEdit>& evnt)
{
	IsEntitySelected = true;
	SelectedEntity = evnt->Entity;
}

void Fracture::LevelEditor::OnReleaseEntityFromEdit(const std::shared_ptr<ReleaseEntityFromEdit>& evnt)
{
	IsEntitySelected = false;
}
