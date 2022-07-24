#pragma once
#ifndef UIELEMENT_H
#define UIELEMENT_H


namespace Fracture
{

	struct UIElement
	{
		virtual void OnRender(bool* p_open) = 0;
		bool Property(const std::string& label, glm::vec3& value, float reset_value = 0);
	};


}

#endif