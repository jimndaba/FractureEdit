#pragma once
#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include "EditingContext.h"

#include "EditorContexts/Scenegraph.h"
#include "EditorContexts/Inspector.h"
#include "EditorContexts/Viewport.h"
#include "EditorContexts/AssetManagerContext.h"

namespace Fracture
{

	class LevelEditor : public EditingContext
	{
	public:
		LevelEditor();
		void OnInit();
		void OnRender(bool* p_open);

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