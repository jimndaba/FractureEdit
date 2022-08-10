#include "EdPCH.h"
#include "EngineOptionsPanels.h"
#include "core/Components.h"
#include "Project/FractureProject.h"
#include "Utils/FileDialogue.h"
#include "EditorApplication.h"
#include "Project/FractureProject.h"

Fracture::CameraOptions::CameraOptions(CameraComponent* component):camera(component)
{
}

void Fracture::CameraOptions::OnRender(bool* p_open)
{
	BeginProps(2);
	Property("Depth of Field", &camera->EnableDepthOfField);
	if (camera->EnableDepthOfField)
	{
		Property("Focal Range", camera->FocalRange);
		Property("Focal Length", camera->FocalLength);
	}
	EndProps();

	BeginProps(2);
	Property("Speed", camera->Speed);
	Property("Damping", camera->Damping);
	Property("Sensitivity", camera->Sensitivity);
	EndProps();
}

Fracture::ProjectOptions::ProjectOptions(FractureProject* p):project(p)
{

}

void Fracture::ProjectOptions::OnRender(bool* p_open)
{
	if (EditorApplication::CurrentProject())
	{
		BeginProps(2);
		PropertyEx("Name", EditorApplication::CurrentProject()->Name);
		PropertyEx("Screenshot path", EditorApplication::CurrentProject()->EditorScreenshotFolderPath);
		ImGui::SameLine();
		if (ImGui::Button("-", ImVec2(16, 16)))
		{
			FileDialogue fd;
			auto path = fd.SelectDirectory();
			if (!path.empty())
			{
				EditorApplication::CurrentProject()->EditorScreenshotFolderPath = path;
			}
		}
		EndProps();
	}
}

Fracture::NewSceneOptions::NewSceneOptions()
{
}

void Fracture::NewSceneOptions::OnRender(bool* p_open)
{
	if (ImGui::BeginPopupModal("New Scene Modal", p_open, ImGuiWindowFlags_AlwaysAutoResize))
	{		
		BeginProps(2);
		PropertyEx("Name", EditorApplication::CurrentScene()->Name);
		EndProps();

		if (!EditorApplication::CurrentScene()->Name.empty())
		{
			if (ImGui::Button("OK", ImVec2(120, 0)))
			{
				*p_open = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::SetItemDefaultFocus();
			ImGui::SameLine();
		}
		if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); *p_open = false; }
		ImGui::EndPopup();
	}
}

Fracture::NewProjectOptions::NewProjectOptions(EditorApplication& application):app(application)
{
}

void Fracture::NewProjectOptions::OnRender(bool* p_open)
{
	
	if (ImGui::BeginPopupModal("New Project", p_open, ImGuiWindowFlags_AlwaysAutoResize))
	{
		std::string project_name;

		BeginProps(2);
		PropertyEx("Project Name", params.Name);
		
		PropertyEx("Project Path", params.path);

		ImGui::SameLine();
		if (ImGui::Button("-"))
		{
			FileDialogue fd;
			params.path = fd.SelectDirectory();
		}
		


		EndProps();

		if (ImGui::Button("OK", ImVec2(120, 0)))
		{
			if (!params.path.empty())
			{
				app.NewProject(params);
			}
			*p_open = false;
			ImGui::CloseCurrentPopup();
		}
		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); *p_open = false; }
		ImGui::EndPopup();
	}
}
