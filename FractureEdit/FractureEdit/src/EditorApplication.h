#pragma once

#include "core/GameWindow.h"
#include "rendering/Device.h"

#include "EditorContexts/LevelEditor.h"

namespace Fracture
{

	class EditorApplication
	{

		std::unique_ptr<GameWindow> mWindow;
		std::unique_ptr<Device> mGraphicsDevice;

		std::unique_ptr<LevelEditor> mLevelEditor;

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

	private:

		bool _ShowLevelEditor = true;
		

	};




}