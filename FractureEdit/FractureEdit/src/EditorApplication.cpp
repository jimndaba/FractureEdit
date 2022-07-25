#include "EdPCH.h"
#include "EditorApplication.h"
#include "EditorContexts/LevelEditor.h"
#include "rendering/RenderGraph.h"

#include "assets/TextureLoader.h"
#include "rendering/Buffer.h"
#include "core/CameraSystem.h"
#include "core/TransformSystem.h"
#include "input/Input.h"
#include "imgui/ImGuizmo.h"
#include "serialisation/SceneSerialiser.h"
#include "Utils/FileDialogue.h"
#include "EditorContexts/Panels/EngineOptionsPanels.h"

bool Fracture::EditorApplication::opt_padding;
std::unique_ptr<Fracture::RenderGraph> mGraph;
std::unique_ptr<Fracture::Input> Fracture::EditorApplication::mInput;
std::shared_ptr<Fracture::Scene> Fracture::EditorApplication::mCurrentScene;
std::unique_ptr<Fracture::Eventbus> Fracture::EditorApplication::EventDispatcher;

std::unique_ptr<Fracture::GameWindow> Fracture::EditorApplication::mWindow;

int  Fracture::EditorApplication::mGuiID;


Fracture::EditorApplication::EditorApplication()
{
}

void Fracture::EditorApplication::Init()
{
	{
		// Setting memory allocators
		OPTICK_SET_MEMORY_ALLOCATOR(
			[](size_t size) -> void* { return operator new(size); },
			[](void* p) { operator delete(p); },
			[]() { /* Do some TLS initialization here if needed */ }
		);
	}
	{
		WindowDescription desc;
		mWindow = std::make_unique<GameWindow>(desc);
		if (mWindow->Init())
			mWindow->MakeCurrent();
	}
	{
		mGraphicsDevice = std::make_unique<Device>();
		mGraphicsDevice->Init();
	}
	{
		Assets = std::make_unique<AssetManager>();
		Assets->Init();
	}	
	{
		EventDispatcher = std::make_unique<Eventbus>();
	}
	{
		mInput = std::make_unique<Input>(mWindow->Context());
	}

	{
		//TODO - Asset File needs to Have Register of converted files
		//Assets->AddStaticMesh("Helmet", "Content\\meshes\\Helmet\\HEML1.fbx");
		Assets->AddStaticMesh("Cube", "Content\\meshes\\Primitives\\Cube.gltf");
		Assets->AddStaticMesh("Cylinder", "Content\\meshes\\Primitives\\Cylinder.gltf");
		Assets->AddStaticMesh("Sphere", "Content\\meshes\\Primitives\\Sphere.gltf");
		Assets->AddStaticMesh("Suzanne", "Content\\meshes\\Primitives\\Suzanne.gltf");
		Assets->AddStaticMesh("Torus", "Content\\meshes\\Primitives\\Torus.gltf");
		Assets->AddStaticMesh("Cone", "Content\\meshes\\Primitives\\Cone.gltf");
		Assets->AddStaticMesh("Plane", "Content\\meshes\\Primitives\\Plane.gltf");
	}
	{
		TextureDescription desc;
		desc.Wrap = TextureWrap::ClampToEdge;
		desc.GenMinMaps = false;
		desc.Path = "Content\\textures\\PointlightIcon.png";

		TextureLoader loader;
		auto texture = loader.Load(desc);
		texture->Name = "PointlightIcon";
		Device::CreateTexture(texture.get());
		Assets->AddTexture(std::move(texture));
	}
	{
		TextureDescription desc;
		desc.Wrap = TextureWrap::ClampToEdge;
		desc.GenMinMaps = false;
		desc.Path = "Content\\textures\\OpenIcon.png";

		TextureLoader loader;
		auto texture = loader.Load(desc);
		texture->Name = "OpenIcon";
		Device::CreateTexture(texture.get());
		Assets->AddTexture(std::move(texture));
	}
	{
		TextureDescription desc;
		desc.Wrap = TextureWrap::ClampToEdge;
		desc.GenMinMaps = false;
		desc.Path = "Content\\textures\\SaveIcon.png";

		TextureLoader loader;
		auto texture = loader.Load(desc);
		texture->Name = "SaveIcon";
		Device::CreateTexture(texture.get());
		Assets->AddTexture(std::move(texture));
	}



	mGuiID = -1;


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	io.ConfigViewportsNoTaskBarIcon = true;


	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends

	if (!ImGui_ImplGlfw_InitForOpenGL(mWindow->Context(), true))
	{
		std::cout << "FAILED TO INIT IMGUI GLFW" << "\n";
	}

	if (!ImGui_ImplOpenGL3_Init("#version 450"))
	{
		std::cout << "FAILED TO INIT IMGUI OPENGL" << "\n";
	}

	ImFont* pFont = io.Fonts->AddFontFromFileTTF("Content/fonts/Nunito-Bold.TTF", 14.0f);

	GuiStyle();

	{
		mLevelEditor = std::make_unique<LevelEditor>();
		mLevelEditor->OnInit();
	}
	{
		mEngineOptions = std::make_unique<EngineOpitonsContext>();
		mEngineOptions->OnInit();
	}
	mCurrentScene = std::make_unique<Scene>();
	
	{
		auto camera = mCurrentScene->AddEntity();
		mCurrentScene->AddTagComponent(camera, "Camera");
		mCurrentScene->AddTransformComponent(camera);
		mCurrentScene->AddCameraComponent(camera);
		HierachyParams p;
		p.Parent = mCurrentScene->RootEntity;
		p.HasParent = true;
		mCurrentScene->AddHierachyComponent(camera, p);
		mCurrentScene->ActiveCamera = camera;
	}
	{
		auto entity = mCurrentScene->AddEntity();
		mCurrentScene->AddTagComponent(entity, "Suzanne");
		mCurrentScene->AddTransformComponent(entity, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0, 0, 0));
		mCurrentScene->AddStaticMeshComponent(entity, "Suzanne", Assets->GetStaticMesh("Suzanne"));

		HierachyParams p;
		p.Parent = mCurrentScene->RootEntity;
		p.HasParent = true;
		mCurrentScene->AddHierachyComponent(entity, p);
	}
	{
		auto entity = mCurrentScene->AddEntity();
		mCurrentScene->AddTagComponent(entity, "Pointlight");
		mCurrentScene->AddTransformComponent(entity, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0, 0, 0));
		mCurrentScene->AddPointlightComponent(entity);

		HierachyParams p;
		p.Parent = mCurrentScene->RootEntity;
		p.HasParent = true;
		mCurrentScene->AddHierachyComponent(entity, p);
	}

	mCurrentContext = mLevelEditor.get();

	EventDispatcher->Publish(std::make_shared<SetSceneForEditing>(*mCurrentScene));

}

void Fracture::EditorApplication::Run()
{
	Init();

	while (!mWindow->ShoulWindowClose() && IsRunning)
	{
		OPTICK_FRAME("MainThread");
		mWindow->PollEvents();
		//mWindow->WaitEvents();
		mGraphicsDevice->Begin();


		Update();	
		Render();

		mWindow->SwapBuffers();


	}

	Shutdown();
}

void Fracture::EditorApplication::Update()
{
	if (mCurrentContext)
	{
		mCurrentContext->OnUpdate();
	}
}

void Fracture::EditorApplication::Render()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGuizmo::BeginFrame();
	mGuiID = -1;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
	ImGuiIO& io = ImGui::GetIO();
	
	DrawMenubar();


	bool p_open = true;
	//static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	if (!opt_padding)
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));



	if (ImGui::Begin("Editor", NULL, window_flags))
	{

		if (!opt_padding)
			ImGui::PopStyleVar();

		ImGui::PopStyleVar(2);

		if (_ShowEditorOptions)
		{
			mEngineOptions->OnRender(&_ShowEditorOptions, mGraphicsDevice.get());
		}


		if (ImGui::BeginTabBar("Contexts"))
		{
			if (ImGui::BeginTabItem("Level Editor", &_ShowLevelEditor))
			{
				mCurrentContext = mLevelEditor.get();
				mLevelEditor->OnRender(&_ShowLevelEditor,mGraphicsDevice.get());
				ImGui::EndTabItem();
			}
			
			if (ImGui::BeginTabItem("RenderGraph Editor", &_ShowGrapEditor))
			{
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Audio Editor", &_ShowAudiEditor))
			{

				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Game", &_ShowAudiEditor))
			{

				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}

		ImGui::SameLine(ImGui::GetContentRegionMax().x * 0.5f);
		ImGui::Button("Play");
		ImGui::SameLine();
		ImGui::Button("Pause");


		ImGui::End();
	}
	
	


	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
	

	


}

void Fracture::EditorApplication::Shutdown()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	OPTICK_SHUTDOWN();
}

void Fracture::EditorApplication::DrawMenubar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("New");
			ImGui::MenuItem("Open");
			ImGui::Separator();
			ImGui::MenuItem("Save");
			ImGui::Separator();
			ImGui::MenuItem("Close");
			if (ImGui::MenuItem("OpenScene"))
			{
				
			}
			ImGui::Separator();
			ImGui::Separator();
			ImGui::MenuItem("Exit");
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			ImGui::MenuItem("Undo");
			ImGui::MenuItem("Redo");
			ImGui::Separator();
			ImGui::MenuItem("Cut");
			ImGui::MenuItem("Copy");
			ImGui::MenuItem("Paste");
			ImGui::MenuItem("Duplicate");
			ImGui::MenuItem("Delete");
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View"))
		{
			ImGui::MenuItem("Options",nullptr, &_ShowEditorOptions);
			ImGui::EndMenu();
		}	
		if (ImGui::BeginMenu("Help"))
		{
			ImGui::MenuItem("View Help");
			ImGui::MenuItem("Getting Started");
			ImGui::MenuItem("About Fracture");
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
}

void Fracture::EditorApplication::Close()
{
	IsRunning = false;
}

void Fracture::EditorApplication::GuiStyle()
{
	ImGuiStyle& style = ImGui::GetStyle();

	/// 0 = FLAT APPEARENCE
	/// 1 = MORE "3D" LOOK
	int is3D = 0;

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);

	colors[ImGuiCol_ChildBg] = ImVec4(0.31f, 0.31f, 0.31f, 0.4f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.18f, 0.18f, 0.18f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.73f, 0.82f, 0.93f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.32f, 0.41f, 0.52f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(1.00f, 1.00f, 1.00f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.77f, 0.77f, 0.77f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(1.00f, 1.00f, 1.00f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.60f, 0.60f, 0.60f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.52f, 0.66f, 0.81f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.51f, 0.51f, 0.51f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.99f, 0.99f, 0.99f, 0.95f);
	colors[ImGuiCol_Tab] = ImVec4(0.25f, 0.25f, 0.25f, 0.86f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.78f, 0.78f, 0.78f, 0.80f);
	colors[ImGuiCol_TabActive] = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.45f, 0.45f, 0.45f, 0.97f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.43f, 0.43f, 0.43f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);




	style.PopupRounding = 2;
	style.WindowPadding = ImVec2(4, 4);
	style.FramePadding = ImVec2(8, 8);
	style.ItemSpacing = ImVec2(4, 4);

	style.ScrollbarSize = 18;

	style.WindowBorderSize = 1;
	style.ChildBorderSize = 1;
	style.PopupBorderSize = 1;
	style.FrameBorderSize = (float)is3D;


	style.WindowRounding = 2;
	style.ChildRounding = 2;
	style.FrameRounding = 2;
	style.ScrollbarRounding = 1;
	style.GrabRounding = 2;

#ifdef IMGUI_HAS_DOCK
	style.TabBorderSize = (float)is3D;
	style.TabRounding = 3;

	colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.22f, 0.23f, 0.25f, 1.00f);
	colors[ImGuiCol_Tab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
	colors[ImGuiCol_DockingPreview] = ImVec4(0.85f, 0.85f, 0.85f, 0.28f);

	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}
#endif
}

Fracture::Eventbus* Fracture::EditorApplication::Dispatcher()
{
	return EventDispatcher.get();
}

Fracture::Scene* Fracture::EditorApplication::CurrentScene()
{
	return mCurrentScene.get();
}

int Fracture::EditorApplication::NextGuiID()
{
	return mGuiID += 1;
}

void Fracture::EditorApplication::OpenScene()
{
	FileDialogue oF;
	auto path = oF.OpenFile(mWindow.get(), "Scene(*.scene)\0 * .scene\0All files(*.*)\0 * .*");
	if (!path.empty())
	{
		SceneSerialiser serialiser(*mCurrentScene, IOMode::Open, SerialiseFormat::Json);
		serialiser.Open(path);
		auto scene = serialiser.ReadScene();
		if (scene)
		{
			EventDispatcher->Publish(std::make_shared<SetSceneForEditing>(*scene));
			mCurrentScene = scene;
		}
	}
}

void Fracture::EditorApplication::SaveProject()
{
}

void Fracture::EditorApplication::LoadProject()
{
}

void Fracture::EditorApplication::CloseProject()
{
}
