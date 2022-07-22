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

namespace Fracture
{

	class EditorApplication
	{

		std::unique_ptr<GameWindow> mWindow;
		std::unique_ptr<Device> mGraphicsDevice;
		std::unique_ptr<LevelEditor> mLevelEditor;
		std::unique_ptr<AssetManager> Assets;
		static std::unique_ptr<Input> mInput;

		std::unique_ptr<OutlineRenderer> mOutlineRenderer;
		std::unique_ptr<SceneRenderer> mSceneRenderer;
		std::unique_ptr<DebugRenderer> mDebugRenderer;
		std::unique_ptr<RenderGraph> mGraph;

		static std::unique_ptr<Scene> mCurrentScene;
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

		static Scene* CurrentScene();

	private:

		bool _ShowLevelEditor = true;
		bool _ShowGrapEditor = true;
		bool _ShowAudiEditor = true;

		EditingContext* mCurrentContext;

	};




}