#pragma once

#include "core/Application.h"
#include "core/GameWindow.h"
#include "rendering/Device.h"
#include "assets/AssetManager.h"
#include "physics/PhysicsManager.h"
#include "EditorContexts/LevelEditor.h"
#include "EditorContexts/RenderGraphEditor.h"
#include "input/Input.h"
#include "events/Eventbus.h"
#include "EditorContexts/OptionsMenuPanel.h"
#include "EditorContexts/Panels/EngineOptionsPanels.h"
#include "Project/FractureProject.h"




namespace Fracture
{
	class ActionSystem;

	class EditorApplication :public Application
	{
		static std::unique_ptr<GameWindow> mWindow;
		static std::unique_ptr<AssetManager> Assets;
		std::shared_ptr<Fracture::RenderGraph> mGraph;
		std::unique_ptr<Device> mGraphicsDevice;
		std::unique_ptr<PhysicsManager> mPhysicsManager;


		std::unique_ptr<LevelEditor> mLevelEditor;
		std::unique_ptr<RenderGraphEditor> mRendergraphEditor;		
		std::unique_ptr<EngineOpitonsContext> mEngineOptions;
		static std::unique_ptr<FractureProject> mProject;
	


		Texture* mPlayIcon;
		Texture* mPauseIcon;


		static std::unique_ptr<Eventbus> EventDispatcher;
		static std::unique_ptr<Input> mInput;		
		std::unique_ptr<NewSceneOptions> mNewSceneModal;
		std::unique_ptr<NewProjectOptions> mNewProjectModal;


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
		static GameWindow* Window();

		static void NewScene();
		static void SaveScene();
		static void OpenScene();

		void OnSaveProject(const std::shared_ptr<SaveProjectEvent>& evnt);

		void NewProject(const ProjectParams& path);
		void SaveProject();
		bool LoadProject();
		void CloseProject();
		
		static FractureProject* CurrentProject();

		static std::unique_ptr<ActionSystem> ActionPlayer;

	private:
		bool _IsProjectDirty = false;
		bool _ShowLevelEditor = true;
		bool _ShowGrapEditor = true;
		bool _ShowAudiEditor = true;
		bool _ShowEditorOptions = false;
		static bool _ShowNewSceneModal;
		static bool _ShowNewProjectModal;

		EditingContext* mCurrentContext = nullptr;
		static int mGuiID;
	};




}