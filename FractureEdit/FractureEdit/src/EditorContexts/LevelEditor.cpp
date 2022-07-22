#include "EdPCH.h"
#include "LevelEditor.h"
#include "../EditorApplication.h"

Fracture::LevelEditor::LevelEditor()
{
}

void Fracture::LevelEditor::OnInit()
{
	mSceneGraph = std::make_unique<ScenegraphView>();
	mInspector = std::make_unique<Inspector>();
	mSceneView = std::make_unique<Viewport>();
	mAssets = std::make_unique<AssetManagerContext>();

	

}

void Fracture::LevelEditor::OnUpdate()
{
	mSceneView->OnUpdate();

}

void Fracture::LevelEditor::OnRender(bool* p_open, Device* device)
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
		mSceneGraph->OnRender(&_ShowScenegraph,device);
	}
	if (_ShowInspector)
	{
		mInspector->OnRender(&_ShowInspector,device);
	}
	if (_ShowViewport)
	{
		mSceneView->OnRender(&_ShowViewport,device);
	}
	if (_ShowAssetManager)
	{
		mAssets->OnRender(&_ShowAssetManager,device);
	}
		

}

void Fracture::LevelEditor::RenderToolbar()
{
	ImVec2 button_size = { 16,16 };

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 0,0 });
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4, 1));

	ImGui::Begin("##Toolbar");
	ImGui::SameLine();
	ImGui::Button("X", button_size);
	ImGui::SameLine();
	ImGui::Button("Y", button_size);
	ImGui::SameLine();
	ImGui::Button("Z", button_size);
	ImGui::SameLine();
	ImGui::Button("W", button_size);
	ImGui::End();

	ImGui::PopStyleVar(2);

}
