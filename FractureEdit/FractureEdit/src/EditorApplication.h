#pragma once

#include "core/GameWindow.h"
#include "rendering/Device.h"

namespace Fracture
{
	//class GameWindow;
	//class Device;

	class EditorApplication
	{

		std::unique_ptr<GameWindow> mWindow;
		std::unique_ptr<Device> mGraphicsDevice;
		bool IsRunning = true;

	public:
		EditorApplication();

		void Init();
		void Run();
		void Update();
		void OnUpdate(float dt);
		void OnRenderBegin();
		void Render();
		void Shutdown();

		void Close();

		

	};




}