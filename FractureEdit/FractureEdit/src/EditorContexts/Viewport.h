#pragma once
#ifndef VIEWPORT_H
#define VIEWPORT_H


#include "EditingContext.h"
#include "imgui/ImGuizmo.h"


#include "core/CameraSystem.h"
#include "core/TransformSystem.h"

#include "rendering/OutlineRenderer.h"
#include "rendering/SceneRenderer.h"
#include "rendering/DebugRenderer.h"


namespace Fracture
{
	struct SelectionContext
	{
		bool isSelected = false;
		UUID entityID;
		float distance;
		glm::vec3 position;
	};

	class Viewport : public EditingContext
	{
	public:
		Viewport(const std::string& name);
		void OnInit();
		void OnLoad();
		void OnUpdate();
		void UpdateCamera(float dt);

		void OnRender(bool* p_open, Device* device);

		void OnSetScene(const std::shared_ptr<SetSceneForEditing>& evnt);
		void OnSetRenderGraph(const std::shared_ptr<SetRenderGraph>& evnt);
		void OnSubmitEntityForEdit(const std::shared_ptr<SubmitEntityForEdit>& evnt);
		void OnReleaseEntityFromEdit(const std::shared_ptr<ReleaseEntityFromEdit>& evnt);


		static CameraComponent* ViewportCamera();

		bool IsFocused();
		bool IsHovered();
		bool IsOnGizomModeButtons();

	private:
		static std::unique_ptr<OutlineRenderer> mOutlineRenderer;
		static std::unique_ptr<SceneRenderer> mSceneRenderer;
		static std::unique_ptr<DebugRenderer> mDebugRenderer;

		Scene* mCurrentScene;
		RenderGraph* mGraph;

		CameraSystem mCameraSystem;
		std::unique_ptr<TransformSystem> mTransformSystem;

		float t;
		float currentTime;
		float dt = 1.0f / 60.0f; 
		glm::vec2 m_InitialMousePosition = glm::vec2(0.0f);
		glm::vec2 mouse_delta = glm::vec2(0.0f);

	private:
		std::string Name;
		bool clearselection = false;
		bool IsOverButton = false;
		bool IsSelectMode = false;
		Texture* mRotateIcon;
		Texture* mScaleIcon;
		Texture* mMoveIcon;
		Texture* mSelectIcon;
		static std::unique_ptr<CameraComponent> mViewportCamera;
		std::vector<SelectionContext> m_SelectionContext;
		glm::vec2 m_ViewportSize;
		bool m_ViewportFocused;
		bool m_ViewportHovered;
		bool IsEditing = false;
		TransformComponent*  mTransform;
		UUID SelectedEntity;
		glm::vec2 m_ViewportBounds[2];

		
		static int gizmoMode;
		ImGuizmo::OPERATION currentImGuizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
		ImGuizmo::MODE currentImGuizmoMode = ImGuizmo::MODE::WORLD;
		void SetImGuizmoOperation(ImGuizmo::OPERATION operation);
		bool IsGizmoValid() const;
		glm::vec2 GetMouseViewportSpace();
	
	};
}


#endif