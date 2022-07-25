#pragma once
#ifndef UIELEMENT_H
#define UIELEMENT_H


namespace Fracture
{

	struct UIElement
	{
		virtual void OnRender(bool* p_open) = 0;
		void BeginProps(int columns);
		void EndProps();

		bool PropertyEx(const std::string& label, std::string& outString, float columnWidth = 100.0f);
		bool Property(const std::string& label, bool* value);
		bool Property(const std::string& label, float& value, float reset_value = 0);
		bool Property(const std::string& label, glm::vec2& value, float reset_value = 0);
		bool Property(const std::string& label, glm::vec3& value, float reset_value = 0);
		bool Property(const std::string& label, glm::vec4& value, float reset_value = 0);
		bool ColorProperty(const std::string& label, glm::vec3& value, float reset_value = 0);
		bool ColorProperty(const std::string& label, glm::vec4& value, float reset_value = 0);
	};


}

#endif