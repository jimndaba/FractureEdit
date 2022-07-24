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
	mSceneView = std::make_unique<Viewport>();
	mAssets = std::make_unique<AssetManagerContext>();

	mSceneView->OnInit();
	{
		mSceneRenderer = std::make_unique<SceneRenderer>();
		mSceneRenderer->Init();

		mOutlineRenderer = std::make_unique<OutlineRenderer>(Device::OutlineContext());
		mOutlineRenderer->Init();

		mDebugRenderer = std::make_unique<DebugRenderer>(Device::DebugContext());
		mDebugRenderer->Init();
	}	
	{
		mGraph = std::make_unique<RenderGraph>();
		mGraph->Setup();
	}

	mCameraSystem = CameraSystem();


}

void Fracture::LevelEditor::OnUpdate()
{
	mOutlineRenderer->Begin();
	mDebugRenderer->Begin();

	float newTime = (float)glfwGetTime();
	float frameTime = newTime - currentTime;
	currentTime = newTime;

	while (frameTime > 0.0)
	{
		float deltaTime = std::min(frameTime, dt);
		//OnUpdate(deltaTime);
		
		UpdateCamera(deltaTime);
		
		
		frameTime -= deltaTime;
		t += deltaTime;
	}




}

void Fracture::LevelEditor::OnRender(bool* p_open, Device* device)
{
	if(IsEntitySelected)
	{
		mOutlineRenderer->DrawOutline(SelectedEntity, EditorApplication::CurrentScene());
	}

	{
		///const auto& camera = EditorApplication::CurrentScene()->GetCameraComponent(EditorApplication::CurrentScene()->ActiveCamera);
		mSceneRenderer->Begin(EditorApplication::CurrentScene(), mSceneView->ViewportCamera(), Device::GeometryContext());
		mSceneRenderer->End(Device::GeometryContext());


		Device::GeometryContext()->Begin();
		Device::GeometryContext()->BindRenderTarget(0);
		Device::GeometryContext()->ClearBuffers((uint32_t)GLClearBufferBit::Color | (uint32_t)GLClearBufferBit::Depth);
		Device::GeometryContext()->SetViewport(0, 0, Device::GeometryContext()->GetViewSize().x, Device::GeometryContext()->GetViewSize().y);

		mGraph->Run(*EditorApplication::CurrentScene());

		Device::GeometryContext()->BindRenderTarget(0);
		Device::GeometryContext()->ClearBuffers((uint32_t)GLClearBufferBit::Color | (uint32_t)GLClearBufferBit::Depth);

		mOutlineRenderer->End();
		mDebugRenderer->End(mSceneView->ViewportCamera());

		Device::SubmitToGpu();
	}

	
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

void Fracture::LevelEditor::UpdateCamera(float dt)
{
	const auto& camera = mSceneView->ViewportCamera();
	if (camera)
	{	
		const glm::vec2& mouse{ Input::GetMousePosition().x,Input::GetMousePosition().y };
		mouse_delta = (mouse - m_InitialMousePosition) * 0.03f;
		m_InitialMousePosition = mouse;
		glm::vec3 pos = camera->Position;


		if (mSceneView->IsHovered() || mSceneView->IsFocused())
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

	mSceneView->OnUpdate();

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
