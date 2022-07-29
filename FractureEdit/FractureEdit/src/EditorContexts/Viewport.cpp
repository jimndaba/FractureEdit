#include "EdPCH.h"
#include "Viewport.h"
#include "core/CameraSystem.h"
#include "rendering/Texture.h"
#include "input/Input.h"
#include "physics/Ray.h"
#include "EditorApplication.h"
#include "scene/Scene.h"
#include "core/Math.h"

int Fracture::Viewport::gizmoMode;
std::unique_ptr<Fracture::CameraComponent> Fracture::Viewport::mViewportCamera;

Fracture::Viewport::Viewport() :EditingContext()
{
}

void Fracture::Viewport::OnInit()
{
	mViewportCamera = std::make_unique<CameraComponent>(UUID());
	mRotateIcon = AssetManager::GetTextureByName("RotateIcon");
	mScaleIcon = AssetManager::GetTextureByName("ScaleIcon");
	mMoveIcon = AssetManager::GetTextureByName("MoveIcon");
	mSelectIcon = AssetManager::GetTextureByName("SelectIcon");
}

void Fracture::Viewport::OnUpdate()
{
	auto io = ImGui::GetIO();	

	if (!Input::IsMouseDown(MOUSECODE::ButtonRight) && m_ViewportHovered || !Input::IsMouseDown(MOUSECODE::ButtonRight) && m_ViewportFocused)
	{
		if (!ImGuizmo::IsUsing() && !Input::IsMouseDown(MOUSECODE::ButtonRight))
		{
			if (Input::IsKeyDown(KeyCode::Q))
			{
				gizmoMode = ImGuizmo::OPERATION::TRANSLATE;
			}
			if (Input::IsKeyDown(KeyCode::W))
			{
				gizmoMode = ImGuizmo::OPERATION::SCALE;
			}
			if (Input::IsKeyDown(KeyCode::E))
			{
				gizmoMode = ImGuizmo::OPERATION::ROTATE;
			}
		}
	}
}

void Fracture::Viewport::OnRender(bool* p_open, Fracture::Device* device)
{
	

	ImGui::Begin("Viewport");
	m_ViewportSize = { ImGui::GetContentRegionAvail().x ,  ImGui::GetContentRegionAvail().y };
	m_ViewportFocused = ImGui::IsWindowFocused();
	m_ViewportHovered = ImGui::IsWindowHovered();

	auto windowSize = ImGui::GetWindowSize();
	ImVec2 minBound = ImGui::GetWindowPos();
	ImVec2 maxBound = { minBound.x + windowSize.x, minBound.y + windowSize.y };
	m_ViewportBounds[0] = { minBound.x, minBound.y };
	m_ViewportBounds[1] = { maxBound.x, maxBound.y };


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

	//TODO need to implement Select mode with no Gizmos?

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 1 , 1 });
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(1, 1));
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.2f, 0.2f));
	ImGui::SetCursorPos(ImVec2{ 10,ImGui::GetContentRegionAvail().y + 40 });
	if (ImGui::ImageButton((ImTextureID)mSelectIcon->RenderID, ImVec2 { 32, 32 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 }))
	{
		IsSelectMode = !IsSelectMode;
		IsOverButton = true;
	}
	ImGui::SameLine();
	if (ImGui::ImageButton((ImTextureID)mRotateIcon->RenderID, ImVec2 { 32, 32 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 }))
	{
		SetImGuizmoOperation(ImGuizmo::OPERATION::ROTATE);
		IsOverButton = true;
	}
	ImGui::SameLine();	
	if (ImGui::ImageButton((ImTextureID)mScaleIcon->RenderID, ImVec2 { 32, 32 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 }))
	{
		SetImGuizmoOperation
		(ImGuizmo::OPERATION::SCALE);
		IsOverButton = true;
	}

	ImGui::SameLine();
	if (ImGui::ImageButton((ImTextureID)mRotateIcon->RenderID, ImVec2 { 32, 32 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 }))
	{
		SetImGuizmoOperation(ImGuizmo::OPERATION::ROTATE);
		IsOverButton = true;
	}

	ImGui::PopStyleVar(2);
	ImGui::PopStyleColor(1);



	if (!IsSelectMode)
	{

	

	ImGuiWindowFlags Gizmoflags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_AlwaysAutoResize;

	if (gizmoMode == ImGuizmo::OPERATION::TRANSLATE)
	{
		SetImGuizmoOperation(ImGuizmo::OPERATION::TRANSLATE);
	}
	if (gizmoMode == ImGuizmo::OPERATION::ROTATE) { SetImGuizmoOperation(ImGuizmo::OPERATION::ROTATE); }
	if (gizmoMode == ImGuizmo::OPERATION::SCALE) {
		SetImGuizmoOperation
		(ImGuizmo::OPERATION::SCALE);
	}
	

	

	if (Input::IsMouseDown(MOUSECODE::ButtonLeft) && m_ViewportHovered || Input::IsMouseDown(MOUSECODE::ButtonLeft) && m_ViewportFocused)
	{
		ImVec2 screen_pos = ImGui::GetMousePos();
		ImVec2 pos = ImGui::GetCursorScreenPos();

		if (IsGizmoValid())
		{
		}
		else
		{
			float width = static_cast<float>(ImGui::GetWindowContentRegionMax().x - ImGui::GetWindowContentRegionMin().x);
			float height = static_cast<float>(ImGui::GetWindowContentRegionMax().y - ImGui::GetWindowContentRegionMin().y);
			float region_x = screen_pos.x - pos.x;
			float region_y = height - ((pos.y - screen_pos.y) * -1);

			auto mouse = GetMouseViewportSpace();

			if (mouse.x > -1.0f && mouse.x < 1.0f && mouse.y > -1.0f && mouse.y < 1.0f)
			{
				const auto& camera = mViewportCamera.get();
				Ray ray = CameraSystem::ScreenPointToRay(*camera, mouse, width, height);
				for (const auto& component : EditorApplication::CurrentScene()->StaticMeshComponents)
				{
					float outT;
					const auto& transform = EditorApplication::CurrentScene()->GetTransformComponent(component->ID);
					if (CameraSystem::RaycastBVH(ray, component->Mesh->bvhRoot, transform->WorldMatrix, outT))
					{
						SelectionContext context;
						context.entityID = component->ID;
						context.distance = outT;
						context.position = ray.origin + (ray.direction * outT);
						context.isSelected = true;
						m_SelectionContext.push_back(context);
					}
					else
					{
						IsEditing = false;
						m_SelectionContext.clear();
						EditorApplication::Dispatcher()->Publish(std::make_shared<ReleaseEntityFromEdit>(UUID()));
					}
				}

				for (const auto& component : EditorApplication::CurrentScene()->PointlightComponents)
				{
					float outT;
					const auto& transform = EditorApplication::CurrentScene()->GetTransformComponent(component->ID);
					if (CameraSystem::RaycastBVH(ray, DebugRenderer::GetBillboadMesh()->bvhRoot, transform->WorldMatrix, outT))
					{
						SelectionContext context;
						context.entityID = component->ID;
						context.distance = outT;
						context.position = ray.origin + (ray.direction * outT);
						context.isSelected = true;
						m_SelectionContext.push_back(context);
						clearselection = false;
					}
					else
					{
						IsEditing = false;
						m_SelectionContext.clear();
						EditorApplication::Dispatcher()->Publish(std::make_shared<ReleaseEntityFromEdit>(UUID()));
					}
				}

				std::sort(m_SelectionContext.begin(), m_SelectionContext.end(), [](auto& a, auto& b) { return a.distance < b.distance; });

				if (!m_SelectionContext.empty())
				{
					EditorApplication::Dispatcher()->Publish(std::make_shared<ReleaseEntityFromEdit>(UUID()));
					EditorApplication::Dispatcher()->Publish(std::make_shared<SubmitEntityForEdit>(m_SelectionContext[0].entityID));
					IsEditing = true;
					m_SelectionContext.clear();
				}
			}
		}
	}	

	float rw = (float)ImGui::GetWindowWidth();
	float rh = (float)ImGui::GetWindowHeight();

	ImGuizmo::SetOrthographic(false);
	ImGuizmo::SetDrawlist();
	ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

	if (IsEditing)
	{
		const auto& camera = mViewportCamera.get();

		if (mTransform)
		{
			glm::mat4 viewMatrix = camera->ViewMatrix;
			glm::mat4 projectionMatrix = camera->ProjectMatrix;
			glm::mat4 delta_transform;

			ImGuizmo::MODE mode = currentImGuizmoMode;
			if (currentImGuizmoOperation == ImGuizmo::OPERATION::SCALE && mode != ImGuizmo::MODE::LOCAL)
				mode = ImGuizmo::MODE::LOCAL;

			if (ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix),
				currentImGuizmoOperation, mode, glm::value_ptr(mTransform->WorldMatrix), glm::value_ptr(delta_transform)))
			{
				if (ImGuizmo::IsUsing())
				{
					glm::vec3 delta_scale;
					glm::vec3 delta_rotation;
					glm::vec3 delta_position;
					Math::DecomposeTransform(delta_transform, delta_position, delta_rotation, delta_scale);

					glm::vec3 scale;
					glm::vec3 rotation;
					glm::vec3 position;
					Math::DecomposeTransform(mTransform->WorldMatrix, position, rotation, scale);

					switch (gizmoMode)
					{
					case ImGuizmo::OPERATION::TRANSLATE:
					{
						mTransform->Position += delta_position;
						mTransform->IsDirty = true;
						break;
					}
					case ImGuizmo::OPERATION::ROTATE:
					{
						mTransform->Rotation += glm::vec3(glm::degrees(delta_rotation.x), glm::degrees(delta_rotation.y), glm::degrees(delta_rotation.z));
						mTransform->IsDirty = true;
						break;
					}
					case ImGuizmo::OPERATION::SCALE:
					{
						mTransform->Scale *= delta_scale;
						mTransform->IsDirty = true;
						break;
					}
					}
				}
			}
		}
	}
	}
	
	
	ImGui::End();

}

void Fracture::Viewport::OnSubmitEntityForEdit(const std::shared_ptr<SubmitEntityForEdit>& evnt)
{
	if (EditorApplication::CurrentScene()->HasTransformComponent(evnt->Entity))
	{
		IsEditing = true;
		mTransform =  EditorApplication::CurrentScene()->GetTransformComponent(evnt->Entity);
	}
}

void Fracture::Viewport::OnReleaseEntityFromEdit(const std::shared_ptr<ReleaseEntityFromEdit>& evnt)
{
	IsEditing = false;
	mTransform = nullptr;
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

bool Fracture::Viewport::IsOnGizomModeButtons()
{
	bool IsOnMode = false;
	
	return IsOnMode;
}

void Fracture::Viewport::SetImGuizmoOperation(ImGuizmo::OPERATION operation)
{
	currentImGuizmoOperation = operation;
}

bool Fracture::Viewport::IsGizmoValid() const
{
	return ImGuizmo::IsOver() || ImGuizmo::IsUsing();
}

glm::vec2 Fracture::Viewport::GetMouseViewportSpace()
{
	auto m = ImGui::GetMousePos();
	m.x -= m_ViewportBounds[0].x;
	m.y -= m_ViewportBounds[0].y;
	auto viewportWidth = m_ViewportBounds[1].x - m_ViewportBounds[0].x;
	auto viewportHeight = m_ViewportBounds[1].y - m_ViewportBounds[0].y;
	return { (m.x / viewportWidth) * 2.0f - 1.0f, ((m.y / viewportHeight) * 2.0f - 1.0f) * -1.0f };
}
