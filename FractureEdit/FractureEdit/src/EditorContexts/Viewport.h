#pragma once
#ifndef VIEWPORT_H
#define VIEWPORT_H


#include "EditingContext.h"

namespace Fracture
{
	class Viewport : public EditingContext
	{
	public:
		Viewport();
		void OnInit();
		void OnUpdate();
		void OnRender(bool* p_open, Device* device);

		CameraComponent* ViewportCamera();

		bool IsFocused();
		bool IsHovered();

	private:
		std::unique_ptr<CameraComponent> mViewportCamera;
		glm::vec2 m_ViewportSize;
		bool m_ViewportFocused;
		bool m_ViewportHovered;
	
	};
}


#endif