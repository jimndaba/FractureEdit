#include "EdPCH.h"
#include "InspectorPanels.h"
#include "core/Components.h"
#include "EditorApplication.h"

Fracture::TransfromComponentPanel::TransfromComponentPanel(TransformComponent* transform):
	component(transform)
{
}

void Fracture::TransfromComponentPanel::OnRender(bool* p_open)
{
	float button_size = 100;
	ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_DefaultOpen;

	ImGui::PushID(EditorApplication::NextGuiID());
	bool open = ImGui::TreeNodeEx("Transform", tree_flags);
	if (open)
	{		
		BeginProps(4);
		Property("Position", component->Position);
		Property("Scale", component->Scale);
		Property("Rotation ", component->Rotation);
		EndProps();

		ImGui::TreePop();
	}
	ImGui::PopID();
}

Fracture::TagComponentPanel::TagComponentPanel(TagComponent* tag):component(tag)
{
}

void Fracture::TagComponentPanel::OnRender(bool* p_open)
{
	float button_size = 100;
	ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_DefaultOpen;
	ImGui::PushID(EditorApplication::NextGuiID());

	bool open = ImGui::TreeNodeEx("Tag", tree_flags);
	if (open)
	{
		ImGuiTableFlags flags = ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersH;

		BeginProps(2);
		PropertyEx("Name", component->Name);
		EndProps();
		ImGui::TreePop();
	}
	ImGui::PopID();
}

Fracture::PointlightPanel::PointlightPanel(PointlightComponent* light):
	component(light)
{
}

void Fracture::PointlightPanel::OnRender(bool* p_open)
{
	float button_size = 100;
	ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_DefaultOpen;
	ImGui::PushID(EditorApplication::NextGuiID());
	bool open = ImGui::TreeNodeEx("Pointlight", tree_flags);
	if (open)
	{
		BeginProps(2);
		Property("Radius", component->Radius);
		Property("Compression", component->Compression);
		Property("Intensity", component->Intensity);
		ColorProperty("Diffuse", component->Diffuse);
		ColorProperty("Specular", component->Specular);
		EndProps();
		ImGui::TreePop();
	}
	ImGui::PopID();
}

Fracture::CameraComonentPanel::CameraComonentPanel(CameraComponent* camera):component(camera)
{
}

void Fracture::CameraComonentPanel::OnRender(bool* p_open)
{
	float button_size = 100;
	ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_DefaultOpen;
	ImGui::PushID(EditorApplication::NextGuiID());
	bool open = ImGui::TreeNodeEx("Pointlight", tree_flags);
	if (open)
	{
		BeginProps(4);
		Property("Position", component->TargetPosition);
		Property("Up", component->Up);
		Property("Right", component->Right);
		EndProps();

		BeginProps(2);
		Property("FoV", component->TargetFoV);
		Property("Near", component->Near);
		Property("Far", component->Far);	
		Property("Pitch", component->TargetPitch);
		Property("Roll", component->TargetRoll);
		Property("Yaw", component->TargetYaw);
		EndProps();
		
		BeginProps(2);
		Property("Speed", component->Speed);
		Property("Sensitivity", component->Sensitivity);
		Property("Damping", component->Damping);
		EndProps();

		BeginProps(2);
		Property("Enable Depth of Field", &component->EnableDepthOfField);
		if (component->EnableDepthOfField)
		{
			Property("Focal Range", component->FocalRange);
			Property("Focal Length", component->FocalLength);
		}
		EndProps();


		ImGui::TreePop();
	}
	ImGui::PopID();
}
