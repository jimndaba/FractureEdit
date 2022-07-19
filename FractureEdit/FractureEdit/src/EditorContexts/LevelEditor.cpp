#include "EdPCH.h"
#include "LevelEditor.h"

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

void Fracture::LevelEditor::OnRender(bool* p_open)
{
	ImGuiIO& io = ImGui::GetIO();
	if (ImGui::BeginTabItem("Level Editor", p_open))
	{
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id);
		}

		if (_ShowScenegraph)
		{
			mSceneGraph->OnRender(&_ShowScenegraph);
		}
		if (_ShowInspector)
		{
			mInspector->OnRender(&_ShowInspector);
		}
		if (_ShowViewport)
		{
			mSceneView->OnRender(&_ShowViewport);
		}
		if (_ShowAssetManager)
		{
			mAssets->OnRender(&_ShowAssetManager);
		}
		ImGui::EndTabItem();
	}
}
