#pragma once
#ifndef UIELEMENT_H
#define UIELEMENT_H


namespace Fracture
{

	struct UIElement
	{
		virtual void OnRender(bool* p_open) = 0;
		virtual void OnAttach();
		virtual void OnDettach();
		void BeginProps(int columns);
		void EndProps();
		bool PropertyImgEx(const std::string& label, const uint32_t image, int ButtonSize);
		bool PropertyImgEx(const std::string& label, const uint32_t image, float& value, float ButtonSize = 64.0f);
		bool PropertyImgEx(const std::string& label, const uint32_t image, glm::vec3& value, float ButtonSize = 64.0f);
	
	
		bool PropertyEx(const std::string& label, std::string& outString, float columnWidth = 100.0f);
		bool Property(const std::string& label, bool* value);
		bool Property(const std::string& label, float& value, float reset_value = 0);
		bool Property(const std::string& label, int& value, float reset_value = 0);
		bool Property(const std::string& label, glm::vec2& value, float reset_value = 0);
		bool Property(const std::string& label, glm::vec3& value, float reset_value = 0);
		bool Property(const std::string& label, glm::vec4& value, float reset_value = 0);
		bool ColorProperty(const std::string& label, glm::vec3& value, float reset_value = 0);
		bool ColorProperty(const std::string& label, glm::vec4& value, float reset_value = 0);
	};


}

#endif