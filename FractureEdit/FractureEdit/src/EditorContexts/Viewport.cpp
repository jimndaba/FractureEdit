#include "EdPCH.h"
#include "Viewport.h"
#include "core/CameraSystem.h"
#include "rendering/Texture.h"

Fracture::Viewport::Viewport() :EditingContext()
{
}

void Fracture::Viewport::OnInit()
{
	mViewportCamera = std::make_unique<CameraComponent>(UUID());
}

void Fracture::Viewport::OnUpdate()
{
}

void Fracture::Viewport::OnRender(bool* p_open, Fracture::Device* device)
{
	ImGui::Begin("Viewport");
	m_ViewportSize = { ImGui::GetContentRegionAvail().x ,  ImGui::GetContentRegionAvail().y };
	m_ViewportFocused = ImGui::IsWindowFocused();
	m_ViewportHovered = ImGui::IsWindowHovered();


	const auto& buffer = device->GeometryContext()->PostProcessReadTarget()->ColorAttachments[0];

	if (buffer)
	{
		ImGui::Image((ImTextureID)(buffer->RenderID), ImVec2{ m_ViewportSize.x,m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		if (ImGui::BeginDragDropTarget())
		{
			const ImGuiPayload* data = ImGui::AcceptDragDropPayload("ModelID");
			if (data)
			{
				//const auto& modelPayload = *(UUID*)data->Data;
				//ActionSystem::Submit<AddStaticMesh>(modelPayload, meshpoint);
				//auto entity = EntityFactory::CreateStaticModel(SceneManager::CurrenScene()->Root->ID, modelPayload,meshpoint);
				//Application::CurrentScene()->AddEntity(std::move(entity));

			}
			ImGui::EndDragDropTarget();
		}

	}



	ImGui::End();
}

Fracture::CameraComponent* Fracture::Viewport::ViewportCamera()
{
	return mViewportCamera.get();
}

bool Fracture::Viewport::IsFocused()
{
	return m_ViewportFocused;
}

bool Fracture::Viewport::IsHovered()
{
	return m_ViewportHovered;
}
