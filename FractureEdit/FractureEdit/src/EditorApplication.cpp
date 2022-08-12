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
#include "serialisation/RendergraphSerialiser.h"
#include "Utils/FileDialogue.h"

#include "Utils/WindowsUtils.h"
#include <ShlObj_core.h>
#include "assets/MeshLoader.h"

#pragma comment(lib, "shell32.lib")

bool Fracture::EditorApplication::opt_padding;

std::unique_ptr<Fracture::Input> Fracture::EditorApplication::mInput;
std::shared_ptr<Fracture::Scene> Fracture::EditorApplication::mCurrentScene;
std::unique_ptr<Fracture::Eventbus> Fracture::EditorApplication::EventDispatcher;
std::unique_ptr<Fracture::AssetManager> Fracture::EditorApplication::Assets;
std::unique_ptr<Fracture::GameWindow> Fracture::EditorApplication::mWindow;
std::unique_ptr<Fracture::FractureProject>  Fracture::EditorApplication::mProject;
std::unique_ptr<Fracture::ActionSystem> Fracture::EditorApplication::ActionPlayer;

int  Fracture::EditorApplication::mGuiID;
bool Fracture::EditorApplication::_ShowNewSceneModal = false;
bool Fracture::EditorApplication::_ShowNewProjectModal = false;

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
	}	
	{
		EventDispatcher = std::make_unique<Eventbus>();
	}
	{
		mInput = std::make_unique<Input>(mWindow->Context());
	}
	{
		ActionPlayer = std::make_unique<ActionSystem>();
	}

	mGuiID = -1;
	{
		TextureDescription desc;
		desc.Wrap = TextureWrap::ClampToEdge;
		desc.GenMinMaps = false;
		desc.Path = "Content\\textures\\PointlightIcon.png";
		desc.Name = "PointlightIcon";

		TextureLoader loader;
		auto texture = loader.Load(desc);
	
		Device::CreateTexture(texture.get());
		Assets->AddTexture(std::move(texture));
	}
	{
		TextureDescription desc;
		desc.Wrap = TextureWrap::ClampToEdge;
		desc.GenMinMaps = false;
		desc.Path = "Content\\textures\\OpenIcon.png";
		desc.Name = "OpenIcon";

		TextureLoader loader;
		auto texture = loader.Load(desc);		
		Device::CreateTexture(texture.get());
		Assets->AddTexture(std::move(texture));
	}
	{
		TextureDescription desc;
		desc.Wrap = TextureWrap::ClampToEdge;
		desc.GenMinMaps = false;
		desc.Path = "Content\\textures\\SaveIcon.png";
		desc.Name = "SaveIcon";

		TextureLoader loader;
		auto texture = loader.Load(desc);	
		Device::CreateTexture(texture.get());
		Assets->AddTexture(std::move(texture));
	}
	{
		TextureDescription desc;
		desc.Wrap = TextureWrap::ClampToEdge;
		desc.GenMinMaps = false;
		desc.Path = "Content\\textures\\PlayIcon.png";
		desc.Name = "PlayIcon";

		TextureLoader loader;
		auto texture = loader.Load(desc);

		Device::CreateTexture(texture.get());
		Assets->AddTexture(std::move(texture));
	}
	{
		TextureDescription desc;
		desc.Wrap = TextureWrap::ClampToEdge;
		desc.GenMinMaps = false;
		desc.Path = "Content\\textures\\PauseIcon.png";
		desc.Name = "PauseIcon";

		TextureLoader loader;
		auto texture = loader.Load(desc);

		Device::CreateTexture(texture.get());
		Assets->AddTexture(std::move(texture));
	}
	{
		TextureDescription desc;
		desc.Wrap = TextureWrap::ClampToEdge;
		desc.GenMinMaps = false;
		desc.Path = "Content\\textures\\RotateIcon.png";
		desc.Name = "RotateIcon";

		TextureLoader loader;
		auto texture = loader.Load(desc);
	
		Device::CreateTexture(texture.get());
		Assets->AddTexture(std::move(texture));
	}
	{
		TextureDescription desc;
		desc.Wrap = TextureWrap::ClampToEdge;
		desc.GenMinMaps = false;
		desc.Path = "Content\\textures\\MoveIcon.png";
		desc.Name = "MoveIcon";


		TextureLoader loader;
		auto texture = loader.Load(desc);
		
		Device::CreateTexture(texture.get());
		Assets->AddTexture(std::move(texture));
	}
	{
		TextureDescription desc;
		desc.Wrap = TextureWrap::ClampToEdge;
		desc.GenMinMaps = false;
		desc.Path = "Content\\textures\\ScaleIcon.png";
		desc.Name = "ScaleIcon";


		TextureLoader loader;
		auto texture = loader.Load(desc);
		
		Device::CreateTexture(texture.get());
		Assets->AddTexture(std::move(texture));
	}
	{
		TextureDescription desc;
		desc.Wrap = TextureWrap::ClampToEdge;
		desc.GenMinMaps = false;
		desc.Path = "Content\\textures\\SelectIcon.png";
		desc.Name = "SelectIcon";

		TextureLoader loader;
		auto texture = loader.Load(desc);
	
		Device::CreateTexture(texture.get());
		Assets->AddTexture(std::move(texture));
	}
	{
		TextureDescription desc;
		desc.Wrap = TextureWrap::ClampToEdge;
		desc.GenMinMaps = false;
		desc.Path = "Content\\textures\\EntityIcon.png";
		desc.Name = "EntityIcon";

		TextureLoader loader;
		auto texture = loader.Load(desc);
		
		Device::CreateTexture(texture.get());
		Assets->AddTexture(std::move(texture));
	}

	{
		TextureDescription desc;
		desc.Wrap = TextureWrap::ClampToEdge;
		desc.GenMinMaps = false;
		desc.Path = "Content\\textures\\DefaultGrid.png";
		desc.Name = "Blank_Texture";

		TextureLoader loader;
		auto texture = loader.Load(desc);

		Device::CreateTexture(texture.get());
		Assets->AddTexture(std::move(texture));
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

	ImFont* pFont = io.Fonts->AddFontFromFileTTF("Content/fonts/Nunito-Bold.TTF", 14.0f);

	GuiStyle();

	{
		mLevelEditor = std::make_unique<LevelEditor>();
		mLevelEditor->OnInit();

		mPlayIcon = AssetManager::GetTextureByName("PlayIcon");
		mPauseIcon = AssetManager::GetTextureByName("PauseIcon");

	}
	{
		mRendergraphEditor = std::make_unique<RenderGraphEditor>();
		mRendergraphEditor->OnInit();
	}
	{
		mEngineOptions = std::make_unique<EngineOpitonsContext>();
		mEngineOptions->OnInit();
	}

	mCurrentContext = mLevelEditor.get();
	mNewSceneModal = std::make_unique<NewSceneOptions>();
	mNewProjectModal = std::make_unique<NewProjectOptions>(*this);

	Dispatcher()->Subscribe(this, &Fracture::EditorApplication::OnSaveProject);
}

void Fracture::EditorApplication::Run()
{
	Init();

	while (!mWindow->ShoulWindowClose() && IsRunning)
	{
		OPTICK_FRAME("MainThread");
		mWindow->PollEvents();

		ActionPlayer->Do();

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
				mCurrentContext = mRendergraphEditor.get();
				mRendergraphEditor->OnRender(&_ShowGrapEditor, mGraphicsDevice.get());
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

		if (_ShowNewSceneModal)
		{
			ImGui::OpenPopup("New Scene Modal");
			mNewSceneModal->OnRender(&_ShowNewSceneModal);
		}


		if (_ShowNewProjectModal)
		{
			ImGui::OpenPopup("New Project");
			mNewProjectModal->OnRender(&_ShowNewProjectModal);
		}


		ImVec2 button_size = {10,10 };
		ImGui::SameLine(ImGui::GetContentRegionMax().x * 0.5f);
		//ImGui::Button("Play");
		//ImGui::SameLine();
		//ImGui::Button("Pause");
		if (ImGui::ImageButton((ImTextureID)mPlayIcon->RenderID, button_size, ImVec2{ 0, 1 }, ImVec2{ 1, 0 }))
		{
		
		}
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)mPauseIcon->RenderID, button_size, ImVec2{ 0, 1 }, ImVec2{ 1, 0 }))
		{

		}


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
			if(ImGui::MenuItem("New Project"))
			{
				
				_ShowNewProjectModal = true;

				
			};

			if (ImGui::MenuItem("Open Project"))
			{
				if (LoadProject())
				{
					std::cout << "Loaded Project\n";
				}


			};
			ImGui::Separator();
			if (ImGui::MenuItem("Save Project"))
			{
				SaveProject();
			};
			ImGui::Separator();
			ImGui::MenuItem("Close Project");
			ImGui::Separator();
			if (ImGui::MenuItem("New Scene"))
			{
				NewScene();
			}
			if (ImGui::MenuItem("Open Scene"))
			{
				OpenScene();
			}
			if (ImGui::MenuItem("Save Scene"))
			{
				SaveScene();
			}			
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
		if (mCurrentScene)
		{
			if (ImGui::BeginMenu("Scene"))
			{
				if (ImGui::BeginMenu("Add"))
				{
					if (ImGui::MenuItem("Cube"))
					{
						auto entity = mCurrentScene->AddEntity();
						mCurrentScene->AddTagComponent(entity, "Cube");
						mCurrentScene->AddTransformComponent(entity, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0, 0, 0));
						mCurrentScene->AddStaticMeshComponent(entity, "Cube", Assets->GetStaticMesh("Cube"));
						HierachyParams p;
						p.Parent = mCurrentScene->RootEntity;
						p.HasParent = true;
						mCurrentScene->AddHierachyComponent(entity, p);

						Dispatcher()->Publish(std::make_shared<SubmitEntityForEdit>(entity));
					}
					if (ImGui::MenuItem("Cylinder"))
					{
						auto entity = mCurrentScene->AddEntity();
						mCurrentScene->AddTagComponent(entity, "Cylinder");
						mCurrentScene->AddTransformComponent(entity, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0, 0, 0));
						mCurrentScene->AddStaticMeshComponent(entity, "Cylinder", Assets->GetStaticMesh("Cylinder"));
						HierachyParams p;
						p.Parent = mCurrentScene->RootEntity;
						p.HasParent = true;
						mCurrentScene->AddHierachyComponent(entity, p);

						Dispatcher()->Publish(std::make_shared<SubmitEntityForEdit>(entity));

					}
					if (ImGui::MenuItem("Suzanne"))
					{
						auto entity = mCurrentScene->AddEntity();
						mCurrentScene->AddTagComponent(entity, "Suzanne");
						mCurrentScene->AddTransformComponent(entity, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0, 0, 0));
						mCurrentScene->AddStaticMeshComponent(entity, "Suzanne", Assets->GetStaticMesh("Suzanne"));
						HierachyParams p;
						p.Parent = mCurrentScene->RootEntity;
						p.HasParent = true;
						mCurrentScene->AddHierachyComponent(entity, p);

						Dispatcher()->Publish(std::make_shared<SubmitEntityForEdit>(entity));
					}
					if (ImGui::MenuItem("Torus"))
					{
						auto entity = mCurrentScene->AddEntity();
						mCurrentScene->AddTagComponent(entity, "Torus");
						mCurrentScene->AddTransformComponent(entity, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0, 0, 0));
						mCurrentScene->AddStaticMeshComponent(entity, "Torus", Assets->GetStaticMesh("Torus"));
						HierachyParams p;
						p.Parent = mCurrentScene->RootEntity;
						p.HasParent = true;
						mCurrentScene->AddHierachyComponent(entity, p);

						Dispatcher()->Publish(std::make_shared<SubmitEntityForEdit>(entity));
					}
					if (ImGui::MenuItem("Sphere"))
					{
						auto entity = mCurrentScene->AddEntity();
						mCurrentScene->AddTagComponent(entity, "Sphere");
						mCurrentScene->AddTransformComponent(entity, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0, 0, 0));
						mCurrentScene->AddStaticMeshComponent(entity, "Sphere", Assets->GetStaticMesh("Sphere"));
						HierachyParams p;
						p.Parent = mCurrentScene->RootEntity;
						p.HasParent = true;
						mCurrentScene->AddHierachyComponent(entity, p);

						Dispatcher()->Publish(std::make_shared<SubmitEntityForEdit>(entity));
					}
					if (ImGui::MenuItem("Cone"))
					{
						auto entity = mCurrentScene->AddEntity();
						mCurrentScene->AddTagComponent(entity, "Cone");
						mCurrentScene->AddTransformComponent(entity, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0, 0, 0));
						mCurrentScene->AddStaticMeshComponent(entity, "Cone", Assets->GetStaticMesh("Cone"));
						HierachyParams p;
						p.Parent = mCurrentScene->RootEntity;
						p.HasParent = true;
						mCurrentScene->AddHierachyComponent(entity, p);

						Dispatcher()->Publish(std::make_shared<SubmitEntityForEdit>(entity));
					}
					if (ImGui::MenuItem("Plane"))
					{
						auto entity = mCurrentScene->AddEntity();
						mCurrentScene->AddTagComponent(entity, "Plane");
						mCurrentScene->AddTransformComponent(entity, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0, 0, 0));
						mCurrentScene->AddStaticMeshComponent(entity, "Plane", Assets->GetStaticMesh("Plane"));
						HierachyParams p;
						p.Parent = mCurrentScene->RootEntity;
						p.HasParent = true;
						mCurrentScene->AddHierachyComponent(entity, p);

						Dispatcher()->Publish(std::make_shared<SubmitEntityForEdit>(entity));
					}
					if (ImGui::MenuItem("Capsule"))
					{
						auto entity = mCurrentScene->AddEntity();
						mCurrentScene->AddTagComponent(entity, "Capsule");
						mCurrentScene->AddTransformComponent(entity, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0, 0, 0));
						mCurrentScene->AddStaticMeshComponent(entity, "Capsule", Assets->GetStaticMesh("Capsule"));
						HierachyParams p;
						p.Parent = mCurrentScene->RootEntity;
						p.HasParent = true;
						mCurrentScene->AddHierachyComponent(entity, p);

						Dispatcher()->Publish(std::make_shared<SubmitEntityForEdit>(entity));
					}
					if (ImGui::MenuItem("Pointlight"))
					{
						auto entity = mCurrentScene->AddEntity();
						mCurrentScene->AddTagComponent(entity, "Pointlight");
						mCurrentScene->AddTransformComponent(entity, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0, 0, 0));
						mCurrentScene->AddPointlightComponent(entity);
						HierachyParams p;
						p.Parent = mCurrentScene->RootEntity;
						p.HasParent = true;
						mCurrentScene->AddHierachyComponent(entity, p);

						Dispatcher()->Publish(std::make_shared<SubmitEntityForEdit>(entity));
					}
					if (ImGui::MenuItem("Static Mesh"))
					{

						FileDialogue oF;
						auto path = oF.OpenFile(mWindow.get(), "fbx(*.fbx)\0 * .fbx\0obj(*.obj)\0 * .obj\0blender(*.blend)\0 * .blend\0glTF(*.gltf)\0 * .gltf\0All files(*.*)\0 * .*");
						if (!path.empty())
						{

							std::string base_filename = path.substr(path.find_last_of("/\\") + 1);
							std::string::size_type const p(base_filename.find_last_of('.'));
							std::string file_without_extension = base_filename.substr(0, p);

							Assets->AddStaticMesh(file_without_extension.c_str(), path.c_str());


							MeshRegistry reg;
							reg.ID = UUID();
							reg.Name = file_without_extension.c_str();
							reg.Path = path.c_str();
							reg.MeshType = MeshRegistry::Type::Static;
							Assets->RegisterMesh(reg);


							auto entity = mCurrentScene->AddEntity();
							mCurrentScene->AddTagComponent(entity, file_without_extension);
							mCurrentScene->AddTransformComponent(entity, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0, 0, 0));
							mCurrentScene->AddStaticMeshComponent(entity, file_without_extension, Assets->GetStaticMesh(file_without_extension.c_str()));

							HierachyParams c;
							c.Parent = mCurrentScene->RootEntity;
							c.HasParent = true;
							mCurrentScene->AddHierachyComponent(entity, c);

							Dispatcher()->Publish(std::make_shared<SubmitEntityForEdit>(entity));
						}


					}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}
		}
		if (ImGui::BeginMenu("View"))
		{
			ImGui::MenuItem("Options",nullptr, &_ShowEditorOptions);
			if(ImGui::MenuItem("Take Screenshot"))
			{
				const auto& texture = mGraphicsDevice->GeometryContext()->PostProcessReadTarget()->ColorAttachments[0];

				int width = texture->Description.Width;
				int height = texture->Description.Height;
				GLsizei nrChannels = 3;
				GLsizei stride = nrChannels * width;
				stride += (stride % 4) ? (4 - stride % 4) : 0;
				GLsizei bufferSize = stride * height;
				std::vector<char> buffer(bufferSize);


				if (mProject->EditorScreenshotFolderPath.empty())
				{
					PWSTR mypicturespath{};
					HRESULT result = SHGetKnownFolderPath(FOLDERID_Pictures, 0, NULL, &mypicturespath);
					std::wstring ws(mypicturespath);
					mProject->EditorScreenshotFolderPath = std::string(ws.begin(), ws.end());
				}

				glPixelStorei(GL_PACK_ALIGNMENT, 4);
				glBindFramebuffer(GL_READ_FRAMEBUFFER, mGraphicsDevice->GeometryContext()->PostProcessReadTarget()->RenderID);
				glReadBuffer(GL_COLOR_ATTACHMENT0);
				glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());
				TextureLoader::SaveImage(mProject->EditorScreenshotFolderPath +"\\fracture_" +  std::to_string(glfwGetTime()) + ".png", width, height, nrChannels, buffer, stride);
				glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
			}

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

Fracture::GameWindow* Fracture::EditorApplication::Window()
{
	return mWindow.get();
}

void Fracture::EditorApplication::NewScene()
{
	if (mProject)
	{
		if (mCurrentScene)
		{
			mCurrentScene.reset();
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
			_ShowNewSceneModal = true;
		}		
		Dispatcher()->Publish(std::make_shared<SetSceneForEditing>(*mCurrentScene.get()));
	}
}

void Fracture::EditorApplication::SaveScene()
{
	SceneSerialiser serialiser(*mCurrentScene, IOMode::Save, SerialiseFormat::Json);
	serialiser.WriteScene();
	serialiser.Save(mProject->ContentDirectory + "\\scenes\\"+ mCurrentScene->Name + ".scene");
	mProject->ActiveScene = mProject->ContentDirectory + "\\scenes\\" + mCurrentScene->Name + ".scene";

	Assets->SaveResources();
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
			Dispatcher()->Publish(std::make_shared<SetSceneForEditing>(*scene));
			mCurrentScene = scene;
		}
	}
}

void Fracture::EditorApplication::OnSaveProject(const std::shared_ptr<SaveProjectEvent>& evnt)
{
	SaveProject();
}

void Fracture::EditorApplication::NewProject(const ProjectParams& p)
{
	if (!p.path.empty())
	{
		int root = _mkdir((p.path + "\\" + p.Name).c_str());
		int bin = _mkdir((p.path + "\\" + p.Name + "\\bin").c_str());
		int src = _mkdir((p.path + "\\" + p.Name + "\\src").c_str());
		int vendor = _mkdir((p.path + "\\" + p.Name + "\\vendor").c_str());
		int intmids = _mkdir((p.path + "\\" + p.Name + "\\int").c_str());

		std::string contentDir = p.path + "\\" + p.Name + "\\bin\\content";
		int check = _mkdir(contentDir.c_str());
		//FRACTURE_INFO("Creating Content Dir: {}", p.path + "\\" + p.Name + "\\bin\\content");

		if (check == 0)
		{
			int models = _mkdir((contentDir + "\\meshes").c_str());		
			int scenes = _mkdir((contentDir + "\\scenes").c_str());
			int rendergraphs = _mkdir((contentDir + "\\rendergraphs").c_str());
			int shaders = _mkdir((contentDir + "\\shaders").c_str());
			int textures = _mkdir((contentDir + "\\textures").c_str());
			int fonts = _mkdir((contentDir + "\\fonts").c_str());
			int scripts = _mkdir((contentDir + "\\scripts").c_str());
			int materials = _mkdir((contentDir + "\\materials").c_str());


			if (mProject)
			{
				CloseProject();
				mProject.reset();
			}

			mProject = std::make_unique<FractureProject>();
			mProject->ID = UUID();
			mProject->Directory = p.path+ "\\" + p.Name;
			mProject->ContentDirectory = contentDir;
			mProject->AssetsFileDirectory = contentDir + "\\AssetRegister.assets";
			mProject->Name = p.Name;
			mWindow->SetTitle("Fracture Engine: " + mProject->Name);

			{
				AssetManagerParams params;
				params.ContentFolder = contentDir;
				params.AssetFilePath = mProject->AssetsFileDirectory;
				Assets.get()->NewAssetRegister(params);
			}
			{
				//TODO - Asset File needs to Have Register of converted files
				//Assets->AddStaticMesh("Helmet", "Content\\meshes\\Helmet\\HEML1.fbx");
				Assets->AddStaticMesh("Cube", "Content\\meshes\\Primitives\\Cube.obj");
				Assets->AddStaticMesh("Cylinder", "Content\\meshes\\Primitives\\Cylinder.obj");
				Assets->AddStaticMesh("Sphere", "Content\\meshes\\Primitives\\Sphere.obj");
				Assets->AddStaticMesh("Suzanne", "Content\\meshes\\Primitives\\Suzanne.obj");
				Assets->AddStaticMesh("Torus", "Content\\meshes\\Primitives\\Torus.obj");
				Assets->AddStaticMesh("Cone", "Content\\meshes\\Primitives\\Cone.obj");
				Assets->AddStaticMesh("Plane", "Content\\meshes\\Primitives\\Plane.obj");
				Assets->AddStaticMesh("Capsule", "Content\\meshes\\Primitives\\Capsule.fbx");
			}
			{
				TextureDescription desc;
				desc.Name = "DefaultHDR";
				desc.Path = "Content\\textures\\open_field.hdr";
				desc.AttachmentTrgt = AttachmentTarget::Color;
				desc.TextureTarget = TextureTarget::Texture2D;
				desc.format = Format::RGB;
				desc.formatType = FormatType::Float;
				desc.internalFormat = InternalFormat::RGB16F;
				desc.minFilter = TextureMinFilter::Linear;
				desc.magFilter = TextureMagFilter::Linear;
				desc.Wrap = TextureWrap::ClampToEdge;
				desc.ID = UUID();

				TextureRegistry reg;
				reg.ID = desc.ID;
				reg.Name = desc.Name;
				reg.Path = desc.Path;
				reg.type = TextureRegistry::TextureType::HDR;
		

				TextureLoader loader;
				auto HDRTexture = loader.LoadHDR(desc);
				reg.Description = desc;
				Assets->RegisterTexture(reg);

				Device::CreateTexture(HDRTexture.get());
				Assets->AddTexture(std::move(HDRTexture));

			}

			
			auto scene = std::make_shared<Scene>();
			{
				auto camera = scene->AddEntity();
				scene->AddTagComponent(camera, "Camera");
				scene->AddTransformComponent(camera);
				scene->AddCameraComponent(camera);
				HierachyParams p;
				p.Parent = scene->RootEntity;
				p.HasParent = true;
				scene->AddHierachyComponent(camera, p);
				scene->ActiveCamera = camera;
			}		
			Dispatcher()->Publish(std::make_shared<SetSceneForEditing>(*scene.get()));
			mCurrentScene = scene;				

			mLevelEditor->OnLoad();

			mGraph = std::make_unique<RenderGraph>(*Device::GeometryContext());
			mGraph->Setup();
			Dispatcher()->Publish(std::make_shared<SetRenderGraph>(*mGraph.get()));

			_ShowNewSceneModal = true;
			SaveProject();			
		}
	}
}

void Fracture::EditorApplication::SaveProject()
{
	if (mProject)
	{
		{
			Serialiser s(IOMode::Save, SerialiseFormat::Json);
			s.BeginStruct("FractureProject");
			s.Property("Directory", mProject->Directory);
			s.Property("Name", mProject->Name);
			s.Property("ContentDirectory", mProject->ContentDirectory);
			s.Property("ActiveScenePath", mProject->ContentDirectory + "\\scenes\\" + mCurrentScene->Name + ".scene");
			s.Property("AssetFileDirectory", mProject->AssetsFileDirectory);
			s.EndStruct();

			s.BeginStruct("ViewportCameraProperties");
			s.Property("Position", mLevelEditor.get()->mSceneView->ViewportCamera()->Position);
			s.Property("Front", mLevelEditor.get()->mSceneView->ViewportCamera()->Front);
			s.Property("Right", mLevelEditor.get()->mSceneView->ViewportCamera()->Right);
			s.Property("Yaw", mLevelEditor.get()->mSceneView->ViewportCamera()->Yaw);
			s.Property("Pitch", mLevelEditor.get()->mSceneView->ViewportCamera()->Pitch);
			s.Property("Roll", mLevelEditor.get()->mSceneView->ViewportCamera()->Roll);
			s.Property("IsDepthOfField", mLevelEditor.get()->mSceneView->ViewportCamera()->EnableDepthOfField);
			s.Property("FocalLength", mLevelEditor.get()->mSceneView->ViewportCamera()->FocalLength);
			s.Property("FocalRange", mLevelEditor.get()->mSceneView->ViewportCamera()->FocalRange);
			s.Property("FoV", mLevelEditor.get()->mSceneView->ViewportCamera()->FoV);
			s.Property("Speed", mLevelEditor.get()->mSceneView->ViewportCamera()->Speed);
			s.Property("Sensitivity", mLevelEditor.get()->mSceneView->ViewportCamera()->Sensitivity);
			s.Property("Damping", mLevelEditor.get()->mSceneView->ViewportCamera()->Damping);
			s.EndStruct();

			s.Save(mProject->Directory + mProject->Name + ".FractureProject");
		}
		SaveScene();

		{
			RenderGraphSerialiser s = RenderGraphSerialiser(*mGraph.get(),IOMode::Save,SerialiseFormat::Json);
			s.WriteGraph();
			s.Save(mProject->ContentDirectory + "\\rendergraphs\\" + "DefaultGraph.RenderGraph");
		}
		Assets.get()->SaveAssetRegister(mProject->AssetsFileDirectory);

		_IsProjectDirty = false;
	}
}

bool Fracture::EditorApplication::LoadProject()
{
	FileDialogue oF;
	auto path = oF.OpenFile(mWindow.get(), "Fracture Project(*.FractureProject)\0 * .FractureProject\0All files(*.*)\0 * .*");
	if (!path.empty())
	{
		if (mProject)
		{
			CloseProject();
		}
		{
			Serialiser serialiser(IOMode::Open, SerialiseFormat::Json);
			serialiser.Open(path);
			if (serialiser.BeginStruct("FractureProject"))
			{
				mProject = std::make_unique<FractureProject>();
				mProject->Name = serialiser.STRING("Name");
				mProject->Directory = serialiser.STRING("Directory");
				mProject->ContentDirectory = serialiser.STRING("ContentDirectory");
				mProject->ActiveScenePath = serialiser.STRING("ActiveScenePath");
				mProject->AssetsFileDirectory = serialiser.STRING("AssetFileDirectory");
				mWindow->SetTitle(mProject->Name);
				serialiser.EndStruct();
			}

			if (serialiser.BeginStruct("ViewportCameraProperties"))
			{
				mLevelEditor.get()->mSceneView->ViewportCamera()->TargetPosition = serialiser.VEC3("Position");
				mLevelEditor.get()->mSceneView->ViewportCamera()->Position = serialiser.VEC3("Position");

				mLevelEditor.get()->mSceneView->ViewportCamera()->Front = serialiser.VEC3("Front");
				mLevelEditor.get()->mSceneView->ViewportCamera()->Right = serialiser.VEC3("Right");

				mLevelEditor.get()->mSceneView->ViewportCamera()->TargetYaw = serialiser.FLOAT("Yaw");
				mLevelEditor.get()->mSceneView->ViewportCamera()->Yaw = serialiser.FLOAT("Yaw");

				mLevelEditor.get()->mSceneView->ViewportCamera()->TargetPitch = serialiser.FLOAT("Pitch");
				mLevelEditor.get()->mSceneView->ViewportCamera()->Pitch = serialiser.FLOAT("Pitch");

				mLevelEditor.get()->mSceneView->ViewportCamera()->TargetRoll = serialiser.FLOAT("Roll");
				mLevelEditor.get()->mSceneView->ViewportCamera()->Roll = serialiser.FLOAT("Roll");

				mLevelEditor.get()->mSceneView->ViewportCamera()->EnableDepthOfField = serialiser.BOOL("IsDepthOfField");
				mLevelEditor.get()->mSceneView->ViewportCamera()->FocalLength = serialiser.FLOAT("FocalLength");
				mLevelEditor.get()->mSceneView->ViewportCamera()->FocalRange = serialiser.FLOAT("FocalRange");


				mLevelEditor.get()->mSceneView->ViewportCamera()->FoV = serialiser.FLOAT("FoV");
				mLevelEditor.get()->mSceneView->ViewportCamera()->Speed = serialiser.FLOAT("Speed");
				mLevelEditor.get()->mSceneView->ViewportCamera()->Sensitivity = serialiser.FLOAT("Sensitivity");
				mLevelEditor.get()->mSceneView->ViewportCamera()->Damping = serialiser.FLOAT("Damping");
				serialiser.EndStruct();
			}
		}
		{
			Assets.get()->LoadAssetRegister(mProject->AssetsFileDirectory);

			if (!mProject->ActiveScenePath.empty())
			{
				SceneSerialiser serialiser(*mCurrentScene, IOMode::Open, SerialiseFormat::Json);
				serialiser.Open(mProject->ActiveScenePath);
				auto scene = serialiser.ReadScene();
				if (scene)
				{
					Dispatcher()->Publish(std::make_shared<SetSceneForEditing>(*scene));
					mCurrentScene = scene;
				}
			}

			mLevelEditor->OnLoad();
			{
				RenderGraphSerialiser s = RenderGraphSerialiser(*mGraph, IOMode::Open, SerialiseFormat::Json);
				s.Open(mProject->ContentDirectory + "\\rendergraphs\\DefaultGraph.RenderGraph");
				mGraph = s.ReadGraph();
				mGraph->Setup();
			}
			Dispatcher()->Publish(std::make_shared<SetRenderGraph>(*mGraph.get()));
		}
		return true;
	}
	return false;

}

void Fracture::EditorApplication::CloseProject()
{
}

Fracture::FractureProject* Fracture::EditorApplication::CurrentProject()
{
	return mProject.get();
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

