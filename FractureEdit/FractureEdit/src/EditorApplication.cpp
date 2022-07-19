#include "EdPCH.h"
#include "EditorApplication.h"
#include "EditorContexts/LevelEditor.h"

bool Fracture::EditorApplication::opt_padding;


Fracture::EditorApplication::EditorApplication()
{
}

void Fracture::EditorApplication::Init()
{
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

	ImFont* pFont = io.Fonts->AddFontFromFileTTF("Content/fonts/Nunito-Bold.TTF", 18.0f);

	GuiStyle();

	mLevelEditor = std::make_unique<LevelEditor>();
	mLevelEditor->OnInit();
}

void Fracture::EditorApplication::Run()
{
	Init();

	while (!mWindow->ShoulWindowClose() && IsRunning)
	{
		mGraphicsDevice->Begin();
		
		Update();	
		Render();

		mWindow->SwapBuffers();
		mWindow->PollEvents();
	}

	Shutdown();
}

void Fracture::EditorApplication::Update()
{
}


void Fracture::EditorApplication::Render()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	//ImGuizmo::BeginFrame();

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
	ImGuiIO& io = ImGui::GetIO();
	DrawMenubar();


	if (ImGui::BeginTabBar("Contexts"))
	{
		static bool opt_fullscreen = true;
		bool p_open = true;

		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		///Submit the DockSpace


		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));



		ImGui::Begin("DockSpace Demo", &p_open, window_flags);

		if (!opt_padding)
			ImGui::PopStyleVar();


		if (opt_fullscreen)
			ImGui::PopStyleVar(2);


		if (_ShowLevelEditor)
		{
			mLevelEditor->OnRender(&_ShowLevelEditor);
		}
	
		if (ImGui::BeginTabItem("RenderGraph Editor", &_ShowLevelEditor))
		{

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Audio Editor", &_ShowLevelEditor))
		{

			ImGui::EndTabItem();
		}

			
		ImGui::End();
		ImGui::EndTabBar();
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
	

	Device::SubmitToGpu();



}

void Fracture::EditorApplication::Shutdown()
{
}

void Fracture::EditorApplication::DrawMenubar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
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
