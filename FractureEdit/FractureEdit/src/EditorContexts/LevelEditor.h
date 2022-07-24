#pragma once
#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include "Scenegraph.h"
#include "Inspector.h"
#include "Viewport.h"
#include "AssetManagerContext.h"

#include "EditingContext.h"

#include "core/CameraSystem.h"

#include "rendering/OutlineRenderer.h"
#include "rendering/SceneRenderer.h"
#include "rendering/DebugRenderer.h"

#include "rendering/RenderGraph.h"



namespace Fracture
{

	struct SubmitEntityForEdit;

	class LevelEditor : public EditingContext
	{
		glm::vec2 m_InitialMousePosition = glm::vec2(0.0f);
		glm::vec2 mouse_delta = glm::vec2(0.0f);
		CameraSystem mCameraSystem;

	public:
		LevelEditor();
		void OnInit();
		void OnUpdate();
		void OnRender(bool* p_open, Device* device);
		void RenderToolbar();

		void UpdateCamera(float dt);

		void OnSubmitEntityForEdit(const std::shared_ptr<SubmitEntityForEdit>& evnt);
		void OnReleaseEntityFromEdit(const std::shared_ptr<ReleaseEntityFromEdit>& evnt);

		std::unique_ptr<ScenegraphView> mSceneGraph;
		std::unique_ptr<Inspector> mInspector;
		std::unique_ptr<Viewport> mSceneView;
		std::unique_ptr<AssetManagerContext> mAssets;

		std::unique_ptr<OutlineRenderer> mOutlineRenderer;
		std::unique_ptr<SceneRenderer> mSceneRenderer;
		std::unique_ptr<DebugRenderer> mDebugRenderer;
		std::unique_ptr<RenderGraph> mGraph;


		bool _ShowScenegraph = true;
		bool _ShowInspector = true;
		bool _ShowViewport = true;
		bool _ShowAssetManager = true;
		float t;
		float currentTime;
		float dt = 1.0f / 60.0f;
		bool IsEntitySelected;
		UUID SelectedEntity;
	};




}

#endif