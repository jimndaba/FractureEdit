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
