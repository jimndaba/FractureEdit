#pragma once

#include "core/GameWindow.h"
#include "rendering/Device.h"
#include "assets/AssetManager.h"
#include "scene/Scene.h"
#include "EditorContexts/LevelEditor.h"
#include "rendering/OutlineRenderer.h"
#include "rendering/SceneRenderer.h"
#include "rendering/DebugRenderer.h"
#include "input/Input.h"
#include "events/Eventbus.h"
#include "EditorContexts/OptionsMenuPanel.h"
#include "Project/FractureProject.h"

namespace Fracture
{

	struct ProjectParams
	{
		std::string Name;
		std::string path;
	};

	class EditorApplication
	{
		static std::unique_ptr<GameWindow> mWindow;
		std::unique_ptr<Device> mGraphicsDevice;
		std::unique_ptr<LevelEditor> mLevelEditor;
		static std::unique_ptr<AssetManager> Assets;
		std::unique_ptr<EngineOpitonsContext> mEngineOptions;
		static std::unique_ptr<FractureProject> mProject;

		Texture* mPlayIcon;
		Texture* mPauseIcon;


		static std::unique_ptr<Eventbus> EventDispatcher;
		static std::unique_ptr<Input> mInput;		
		static std::shared_ptr<Scene> mCurrentScene;


		bool IsRunning = true;
		static bool opt_padding;

	public:
		EditorApplication();

		void Init();
		void Run();
		void Update();
		void Render();
		void Shutdown();
		void DrawMenubar();
		void Close();
		void GuiStyle();
		static Eventbus* Dispatcher();
		static Scene* CurrentScene();
		static int NextGuiID();

		static void NewScene();
		static void SaveScene();
		static void OpenScene();

		void NewProject(const ProjectParams& path);
		void SaveProject();
		void LoadProject();
		void CloseProject();

		static FractureProject* CurrentProject();


	private:
		bool _IsProjectDirty = false;
		bool _ShowLevelEditor = true;
		bool _ShowGrapEditor = true;
		bool _ShowAudiEditor = true;
		bool _ShowEditorOptions = false;

		EditingContext* mCurrentContext = nullptr;
		static int mGuiID;
	};




}