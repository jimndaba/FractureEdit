#include "EdPCH.h"
#include "LevelEditor.h"
#include "../EditorApplication.h"
#include "events/Eventbus.h"

bool Fracture::LevelEditor::IsEntitySelected;
Fracture::UUID Fracture::LevelEditor::SelectedEntity;

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

	glfwSetKeyCallback(EditorApplication::Window()->Context(), key_callback);

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

void Fracture::LevelEditor::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
	if (IsEntitySelected)
	{
		if (key == GLFW_KEY_DELETE)
		{
			EditorApplication::ActionPlayer->Submit<DeleteEntityAction>(SelectedEntity);
		}
		
		if (mods == GLFW_MOD_CONTROL)
		{
			//Duplicate
			if (key == GLFW_KEY_D && action == GLFW_PRESS)
			{
				EditorApplication::ActionPlayer->Submit<DuplicateEntityAction>(SelectedEntity);

				//for (const auto& entity : SceneGraphFrame::MultiSelectedEntity())
				//{
				//	SceneGraphFrame::ClearSelection();
				//	ActionSystem::Submit<DuplicateEntityAction>(entity);
				//}
			}
		}
	
	}
	
	if (mods == GLFW_MOD_CONTROL)
	{
		//Select ALL
		if (key == GLFW_KEY_A && action == GLFW_PRESS)
		{
			//for (auto& entity : SceneManager::CurrenScene()->Entities)
			///{
			//	SceneGraphFrame::AddToSelection(entity->ID);
			//}
		}
		//New
		if (key == GLFW_KEY_N && action == GLFW_PRESS)
		{
			//FRACTURE_INFO("New");
			//NewProject();

		}
		//Open
		if (key == GLFW_KEY_O && action == GLFW_PRESS)
		{
			//FRACTURE_INFO("Open");
			//std::string path = FileDialogue::OpenFile(".fracture");
			//if (!path.empty())
			//{
			//	//OpenProject(path);
			//}
		}
		//Save
		if (key == GLFW_KEY_S && action == GLFW_PRESS)
		{			
			EditorApplication::Dispatcher()->Publish(std::make_shared<SaveProjectEvent>());
		}
		//Undo
		//if (key == GLFW_KEY_Z && action == GLFW_PRESS)
		//{
		//	ActionSystem::UndoLast();
		//}
		//Redo
		//if (key == GLFW_KEY_Y && action == GLFW_PRESS)
		//{
		//	ActionSystem::RedoLast();
		//}
	}
	
}