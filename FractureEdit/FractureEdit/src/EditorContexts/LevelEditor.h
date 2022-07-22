#pragma once
#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include "Scenegraph.h"
#include "Inspector.h"
#include "Viewport.h"
#include "AssetManagerContext.h"

#include "EditingContext.h"


#include "rendering/OutlineRenderer.h"
#include "rendering/SceneRenderer.h"
#include "rendering/DebugRenderer.h"

#include "rendering/RenderGraph.h"

namespace Fracture
{

	class LevelEditor : public EditingContext
	{
		glm::vec2 m_InitialMousePosition = glm::vec2(0.0f);
		glm::vec2 mouse_delta = glm::vec2(0.0f);

	public:
		LevelEditor();
		void OnInit();
		void OnUpdate();
		void OnRender(bool* p_open, Device* device);
		void RenderToolbar();

		std::unique_ptr<ScenegraphView> mSceneGraph;
		std::unique_ptr<Inspector> mInspector;
		std::unique_ptr<Viewport> mSceneView;
		std::unique_ptr<AssetManagerContext> mAssets;

		bool _ShowScenegraph = true;
		bool _ShowInspector = true;
		bool _ShowViewport = true;
		bool _ShowAssetManager = true;
	};




}

#endif