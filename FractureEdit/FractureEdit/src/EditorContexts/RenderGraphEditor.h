#pragma once
#ifndef RENDERGRAPHEDITOR_H
#define RENDERGRAPHEDITOR_H

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

#include "RendergraphInspector.h"

namespace Fracture
{

	struct SubmitEntityForEdit;

	class RenderGraphEditor : public EditingContext
	{
		
		Scene* mCurrenScene;
		Texture* mSaveIcon;
		Texture* mOpenIcon;

	public:
		RenderGraphEditor();
		void OnInit();
		void OnUpdate();
		void OnLoad();
		void OnRender(bool* p_open, Device* device);
		void RenderToolbar();

		void OnSetScene(const std::shared_ptr<SetSceneForEditing>& evnt);
		void OnSetRenderGraph(const std::shared_ptr<SetRenderGraph>& evnt);
		void OnSubmitEntityForEdit(const std::shared_ptr<SubmitEntityForEdit>& evnt);
		void OnReleaseEntityFromEdit(const std::shared_ptr<ReleaseEntityFromEdit>& evnt);


		std::unique_ptr<Viewport> mSceneView;
		std::unique_ptr<RenderGraphInspector> mInspector;

		RenderGraph* mGraph;

		bool _ShowViewport = true;
		bool _ShowInspector = true;

		bool IsEntitySelected;
		UUID SelectedEntity;
	};
}
#endif