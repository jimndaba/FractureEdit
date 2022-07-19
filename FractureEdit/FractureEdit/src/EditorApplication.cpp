#include "EdPCH.h"
#include "EditorApplication.h"



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
}

void Fracture::EditorApplication::Run()
{
	Init();

	while (!mWindow->ShoulWindowClose() && IsRunning)
	{
		mGraphicsDevice->Begin();

		
		
		Update();
		OnRenderBegin();
		Render();
		mWindow->SwapBuffers();
		mWindow->PollEvents();
	}

	Shutdown();
}

void Fracture::EditorApplication::Update()
{
}

void Fracture::EditorApplication::OnUpdate(float dt)
{
}

void Fracture::EditorApplication::OnRenderBegin()
{
}

void Fracture::EditorApplication::Render()
{
	Device::SubmitToGpu();
}

void Fracture::EditorApplication::Shutdown()
{
}

void Fracture::EditorApplication::Close()
{
	IsRunning = false;
}
