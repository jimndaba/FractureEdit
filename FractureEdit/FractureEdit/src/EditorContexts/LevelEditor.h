#pragma once
#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include "Scenegraph.h"
#include "Inspector.h"
#include "Viewport.h"
#include "AssetManagerContext.h"

#include "EditingContext.h"

#include "core/CameraSystem.h"
#include "core/TransformSystem.h"

#include "rendering/OutlineRenderer.h"
#include "rendering/SceneRenderer.h"
#include "rendering/DebugRenderer.h"

#include "rendering/RenderGraph.h"



namespace Fracture
{

	struct SubmitEntityForEdit;

	class LevelEditor : public EditingContext
	{
		Scene* mCurrenScene;
		Texture* mSaveIcon;
		Texture* mOpenIcon;
		RenderGraph* mGraph;

	public:
		LevelEditor();
		void OnInit();
		void OnUpdate();
		void OnLoad();
		void OnRender(bool* p_open, Device* device);
		void RenderToolbar();		

		void OnSetScene(const std::shared_ptr<SetSceneForEditing>& evnt);
		void OnSetRenderGraph(const std::shared_ptr<SetRenderGraph>& evnt);
		void OnSubmitEntityForEdit(const std::shared_ptr<SubmitEntityForEdit>& evnt);
		void OnReleaseEntityFromEdit(const std::shared_ptr<ReleaseEntityFromEdit>& evnt);

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

		std::unique_ptr<ScenegraphView> mSceneGraph;
		std::unique_ptr<Inspector> mInspector;
		std::unique_ptr<Viewport> mSceneView;
		std::unique_ptr<AssetManagerContext> mAssets;

		

		bool _ShowScenegraph = true;
		bool _ShowInspector = true;
		bool _ShowViewport = true;
		bool _ShowAssetManager = true;
		float t;
		float currentTime;
		float dt = 1.0f / 60.0f;
		static bool IsEntitySelected;
		static UUID SelectedEntity;
	};




}

#endif