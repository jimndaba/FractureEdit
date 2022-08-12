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
std::unique_ptr<Fracture::OutlineRenderer> Fracture::Viewport::mOutlineRenderer;
std::unique_ptr<Fracture::SceneRenderer> Fracture::Viewport::mSceneRenderer;
std::unique_ptr<Fracture::DebugRenderer> Fracture::Viewport::mDebugRenderer;

Fracture::Viewport::Viewport(const std::string& name) :EditingContext(),Name(name)
{
	currentTime = (float)glfwGetTime();
}

void Fracture::Viewport::OnInit()
{
	if(!mViewportCamera)
		mViewportCamera = std::make_unique<CameraComponent>(UUID());

	if (!mSceneRenderer) {
		mSceneRenderer = std::make_unique<SceneRenderer>();
		mSceneRenderer->Init();
	}

	if (!mOutlineRenderer)
	{
		mOutlineRenderer = std::make_unique<OutlineRenderer>(Device::OutlineContext());
		mOutlineRenderer->Init();
	}

	if (!mDebugRenderer)
	{
		mDebugRenderer = std::make_unique < DebugRenderer>(Device::DebugContext());
		mDebugRenderer->Init();
	}

	mTransformSystem = std::make_unique<TransformSystem>();

	mRotateIcon = AssetManager::GetTextureByName("RotateIcon");
	mScaleIcon = AssetManager::GetTextureByName("ScaleIcon");
	mMoveIcon = AssetManager::GetTextureByName("MoveIcon");
	mSelectIcon = AssetManager::GetTextureByName("SelectIcon");	
	SetImGuizmoOperation(ImGuizmo::OPERATION::TRANSLATE);
}

void Fracture::Viewport::OnLoad()
{
	mDebugRenderer->Onload();
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

	

	if (mCurrentScene)
	{
		mOutlineRenderer->Begin();
		mDebugRenderer->Begin();


		float newTime = (float)glfwGetTime();
		float frameTime = newTime - currentTime;
		currentTime = newTime;

		while (frameTime > 0.0)
		{
			float deltaTime = std::min(frameTime, dt);
			{
				UpdateCamera(deltaTime);
			}

			frameTime -= deltaTime;
			t += deltaTime;
		}
		mTransformSystem->Update(mCurrentScene->RootEntity, glm::mat4(1.0));
	}




}

void Fracture::Viewport::UpdateCamera(float dt)
{
	const auto& camera = mViewportCamera.get();
	if (camera)
	{
		const glm::vec2& mouse{ Input::GetMousePosition().x,Input::GetMousePosition().y };
		mouse_delta = (mouse - m_InitialMousePosition) * 0.03f;
		m_InitialMousePosition = mouse;
		glm::vec3 pos = camera->Position;


		if (IsHovered() || IsFocused())
		{
			if (ImGui::IsMouseDown(ImGuiMouseButton_Right))
			{
				if (Input::IsKeyDown(KeyCode::W))
				{
					pos += camera->Front * camera->Speed * dt * 1000.0f;
				}
				if (Input::IsKeyDown(KeyCode::A))
				{
					pos -= camera->Right * camera->Speed * dt * 1000.0f;
				}
				if (Input::IsKeyDown(KeyCode::S))
				{
					pos -= camera->Front * camera->Speed * dt * 1000.0f;
				}
				if (Input::IsKeyDown(KeyCode::D))
				{
					pos += camera->Right * camera->Speed * dt * 1000.0f;
				}
				if (Input::IsKeyDown(KeyCode::Q))
				{
					pos += camera->Up * camera->Speed * dt * 1000.0f;
				}
				if (Input::IsKeyDown(KeyCode::E))
				{
					pos -= camera->Up * camera->Speed * dt * 1000.0f;
				}

				mCameraSystem.OnMouseInput(*camera, mouse_delta.x, mouse_delta.y, false);
				mCameraSystem.OnTranslate(*camera, pos.x, pos.y, pos.z);
			}
		}

	}

	mCameraSystem.Update(*camera, 1.0f / 60.0f);
	mCameraSystem.UpdateViewMatrix(*camera);
	mCameraSystem.UpdateProjectionMatrix(*camera, Device::ScreenSize());


}

void Fracture::Viewport::OnRender(bool* p_open, Fracture::Device* device)
{
	if(mCurrentScene)
	{
		if (IsEditing)
		{
			mOutlineRenderer->DrawOutline(SelectedEntity, mCurrentScene);
		}
		if (mGraph)
		{
			mSceneRenderer->Begin(mCurrentScene, mViewportCamera.get(), Device::GeometryContext());
			mSceneRenderer->End(Device::GeometryContext());


			Device::GeometryContext()->Begin();
			Device::GeometryContext()->BindRenderTarget(0);
			Device::GeometryContext()->ClearBuffers((uint32_t)GLClearBufferBit::Color | (uint32_t)GLClearBufferBit::Depth);
			Device::GeometryContext()->SetViewport(0, 0, Device::GeometryContext()->GetViewSize().x, Device::GeometryContext()->GetViewSize().y);

			mGraph->Run(*EditorApplication::CurrentScene(), mViewportCamera.get());

			Device::GeometryContext()->BindRenderTarget(0);
			Device::GeometryContext()->ClearBuffers((uint32_t)GLClearBufferBit::Color | (uint32_t)GLClearBufferBit::Depth);
			
			mOutlineRenderer->End();
			mDebugRenderer->End(mViewportCamera.get());


			Device::SubmitToGpu();
		}
	}
	ImGui::Begin(Name.c_str());
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
	ImVec2 button_size = ImVec2{ 16, 16 };
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 1 , 1 });
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(1, 1));
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.2f, 0.2f));
	ImGui::SetCursorPos(ImVec2{ 10,ImGui::GetContentRegionAvail().y + 40 });

	if (ImGui::ImageButton((ImTextureID)mSelectIcon->RenderID, button_size, ImVec2{ 0, 1 }, ImVec2{ 1, 0 }))
	{
		IsSelectMode = !IsSelectMode;
		IsOverButton = true;
	}
	ImGui::SameLine();
	if (ImGui::ImageButton((ImTextureID)mRotateIcon->RenderID, button_size, ImVec2{ 0, 1 }, ImVec2{ 1, 0 }))
	{
		SetImGuizmoOperation(ImGuizmo::OPERATION::ROTATE);
		IsOverButton = true;
	}
	ImGui::SameLine();	
	if (ImGui::ImageButton((ImTextureID)mScaleIcon->RenderID, button_size, ImVec2{ 0, 1 }, ImVec2{ 1, 0 }))
	{
		SetImGuizmoOperation
		(ImGuizmo::OPERATION::SCALE);
		IsOverButton = true;
	}
	ImGui::SameLine();
	if (ImGui::ImageButton((ImTextureID)mRotateIcon->RenderID, button_size, ImVec2{ 0, 1 }, ImVec2{ 1, 0 }))
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
				}
				if (m_SelectionContext.empty())
				{
					EditorApplication::Dispatcher()->Publish(std::make_shared<ReleaseEntityFromEdit>(UUID()));
				}

				if (!m_SelectionContext.empty())
				{
					std::sort(m_SelectionContext.begin(), m_SelectionContext.end(), [](auto& a, auto& b) { return a.distance < b.distance; });

					EditorApplication::Dispatcher()->Publish(std::make_shared<ReleaseEntityFromEdit>(UUID()));
					EditorApplication::ActionPlayer->Submit<SelectEntityAction>(m_SelectionContext[0].entityID);		
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
							TransformSystem::Translate(*mTransform, delta_position);
							break;
						}
						case ImGuizmo::OPERATION::ROTATE:
						{
							TransformSystem::Rotate(*mTransform, glm::vec3(glm::degrees(delta_rotation.x), glm::degrees(delta_rotation.y), glm::degrees(delta_rotation.z)));
							break;
						}
						case ImGuizmo::OPERATION::SCALE:
						{
							TransformSystem::Scale(*mTransform, delta_scale);
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

void Fracture::Viewport::OnSetScene(const std::shared_ptr<SetSceneForEditing>& evnt)
{
	mCurrentScene = &evnt->scene;
	mTransformSystem->SetScene(&evnt->scene);
}

void Fracture::Viewport::OnSetRenderGraph(const std::shared_ptr<SetRenderGraph>& evnt)
{
	mGraph = &evnt->Graph;
}

void Fracture::Viewport::OnSubmitEntityForEdit(const std::shared_ptr<SubmitEntityForEdit>& evnt)
{
	if (EditorApplication::CurrentScene()->HasTransformComponent(evnt->Entity))
	{
		IsEditing = true;
		mTransform =  EditorApplication::CurrentScene()->GetTransformComponent(evnt->Entity);
		SelectedEntity = evnt->Entity;
	}
}

void Fracture::Viewport::OnReleaseEntityFromEdit(const std::shared_ptr<ReleaseEntityFromEdit>& evnt)
{
	IsEditing = false;
	mTransform = nullptr;
	SelectedEntity = UUID();
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
	gizmoMode = operation;
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
