#pragma once
#ifndef VIEWPORT_H
#define VIEWPORT_H


#include "EditingContext.h"
#include "imgui/ImGuizmo.h"

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
		Viewport();
		void OnInit();
		void OnUpdate();
		void OnRender(bool* p_open, Device* device);
		void OnSubmitEntityForEdit(const std::shared_ptr<SubmitEntityForEdit>& evnt);
		void OnReleaseEntityFromEdit(const std::shared_ptr<ReleaseEntityFromEdit>& evnt);


		static CameraComponent* ViewportCamera();

		bool IsFocused();
		bool IsHovered();

	private:
		static std::unique_ptr<CameraComponent> mViewportCamera;
		std::vector<SelectionContext> m_SelectionContext;
		glm::vec2 m_ViewportSize;
		bool m_ViewportFocused;
		bool m_ViewportHovered;
		bool IsEditing = false;
		TransformComponent*  mTransform;
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