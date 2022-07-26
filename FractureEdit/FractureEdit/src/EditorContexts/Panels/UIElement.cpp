#include "EdPCH.h"
#include "UIElement.h"
#include <imgui/imgui_internal.h>
#include "EditorApplication.h"

void Fracture::UIElement::OnAttach()
{
}

void Fracture::UIElement::OnDettach()
{
}

void Fracture::UIElement::BeginProps(int columns)
{
	ImGuiTableFlags flags = ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersH;
	ImGuiTableColumnFlags cf = ImGuiTableColumnFlags_WidthFixed;
	ImGui::BeginTable(std::to_string(EditorApplication::NextGuiID()).c_str(), columns, flags);
	ImGui::TableSetupColumn("label", cf, 100.0f);
}

void Fracture::UIElement::EndProps()
{
	ImGui::EndTable();
}

bool Fracture::UIElement::PropertyImgEx(const std::string& label, const uint32_t image, glm::vec3& value,float ButtonSize)
{
	bool dirty = false;
	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 1.5f;
	ImVec2 buttonSize = { lineHeight + 0.0f, lineHeight };

	ImGui::PushID(EditorApplication::NextGuiID());

	ImGui::TableNextColumn();

	ImGui::Text(label.c_str());

	ImGui::TableNextColumn();
	{
		if (ImGui::ImageButton((ImTextureID)image, ImVec2(64, 64), ImVec2{ 0, 1 }, ImVec2{ 1, 0 }))
		{
			dirty = true;
		}
	}
	ImGui::SameLine();
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 0,0 });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.8f,0.30f,0.30f,1.0f });
		if (ImGui::Button("-", buttonSize))
		{
			value = glm::vec3(1.0f);
			dirty = true;
		}
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
		ImGui::SameLine();
		ImGui::PushItemWidth(-5);
		float col[3] = { value.x,value.y,value.z };

		ImGui::PushItemWidth(32);
		ImGuiColorEditFlags flag = ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview;
		if (ImGui::ColorPicker3("##color", col, flag))
		{
			value = glm::vec3(col[0], col[1], col[2]);
			dirty = true;
		}
		ImGui::PopItemWidth();
	}
	ImGui::PopID();
	return dirty;
}

bool Fracture::UIElement::PropertyImgEx(const std::string& label, const uint32_t image, float& value, float ButtonSize)
{
	bool dirty = false;
	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 1.5f;
	ImVec2 buttonSize = { lineHeight + 0.0f, lineHeight };

	ImGui::PushID(EditorApplication::NextGuiID());

	ImGui::TableNextColumn();

	ImGui::Text(label.c_str());

	ImGui::TableNextColumn();
	{
		if (ImGui::ImageButton((ImTextureID)image, ImVec2(64, 64), ImVec2{ 0, 1 }, ImVec2{ 1, 0 }))
		{
			dirty = true;
		}
	}
	ImGui::SameLine();
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 0,0 });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.8f,0.30f,0.30f,1.0f });
		if (ImGui::Button("-", buttonSize))
		{
			value = 0.0f;
		}
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
		ImGui::SameLine();
		ImGui::PushItemWidth(-5);
		ImGui::DragFloat("##value", &value, 0.01f, -10000.0f, 10000.0f, "%.2f");
	}
	ImGui::PopID();
	return dirty;
}

bool Fracture::UIElement::PropertyImgEx(const std::string& label, const uint32_t image, int ButtonSize)
{
	bool dirty = false;
	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 1.5f;
	ImVec2 buttonSize = { lineHeight + 0.0f, lineHeight };

	ImGui::PushID(EditorApplication::NextGuiID());

	ImGui::TableNextColumn();

	ImGui::Text(label.c_str());

	ImGui::TableNextColumn();
	if (ImGui::ImageButton((ImTextureID)image, ImVec2(ButtonSize, ButtonSize), ImVec2{ 0, 1 }, ImVec2{ 1, 0 }))
	{
		dirty = true;
	}	
	ImGui::PopID();
	return dirty;
}

bool Fracture::UIElement::PropertyEx(const std::string& label, std::string& outString, float columnWidth)
{
	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 1.5f;
	ImVec2 buttonSize = { lineHeight + 0.0f, lineHeight };

	ImGui::PushID(EditorApplication::NextGuiID());

	ImGui::TableNextColumn();

	ImGui::Text(label.c_str());

	ImGui::TableNextColumn();

	char buffer[256];
	memset(buffer, 0, sizeof(buffer));
	strcpy_s(buffer, sizeof(buffer), outString.c_str());
	ImGui::PushItemWidth(columnWidth);
	if (ImGui::InputText("##pr", buffer, sizeof(buffer)))
	{
		outString = std::string(buffer);	
	}
	ImGui::PopItemWidth();
	ImGui::PopID();
	return false;
}

bool Fracture::UIElement::Property(const std::string& label, const std::string& text)
{
	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 1.5f;
	ImVec2 buttonSize = { lineHeight + 0.0f, lineHeight };

	ImGui::PushID(EditorApplication::NextGuiID());

	ImGui::TableNextColumn();

	ImGui::Text(label.c_str());

	ImGui::TableNextColumn();
	{
		ImGui::PushItemWidth(-5);
		ImGui::Text(text.c_str());
	}
	ImGui::PopID();
	return false;
}

bool Fracture::UIElement::Property(const std::string& label, bool* value)
{
	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 1.5f;
	ImVec2 buttonSize = { lineHeight + 0.0f, lineHeight };

	ImGui::PushID(EditorApplication::NextGuiID());

	ImGui::TableNextColumn();

	ImGui::Text(label.c_str());

	ImGui::TableNextColumn();
	{
		ImGui::PushItemWidth(-5);
		ImGui::Checkbox("##value",value);
	}
	ImGui::PopID();
	return false;
}

bool Fracture::UIElement::Property(const std::string& label, float& value, float reset_value)
{
	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 1.5f;
	ImVec2 buttonSize = { lineHeight + 0.0f, lineHeight };

	ImGui::PushID(EditorApplication::NextGuiID());

	ImGui::TableNextColumn();

	ImGui::Text(label.c_str());

	ImGui::TableNextColumn();
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 0,0 });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.8f,0.30f,0.30f,1.0f });
		if (ImGui::Button("-", buttonSize))
		{
			value = reset_value;
		}
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
		ImGui::SameLine();
		ImGui::PushItemWidth(-5);
		ImGui::DragFloat("##value", &value, 0.01f, -10000.0f, 10000.0f, "%.2f");
	}	
	ImGui::PopID();
	return false;
}

bool Fracture::UIElement::Property(const std::string& label, int& value, float reset_value)
{
	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 1.5f;
	ImVec2 buttonSize = { lineHeight + 0.0f, lineHeight };

	ImGui::PushID(EditorApplication::NextGuiID());

	ImGui::TableNextColumn();

	ImGui::Text(label.c_str());

	ImGui::TableNextColumn();
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 0,0 });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.8f,0.30f,0.30f,1.0f });
		if (ImGui::Button("-", buttonSize))
		{
			value = reset_value;
		}
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
		ImGui::SameLine();
		ImGui::PushItemWidth(-5);
		ImGui::DragInt("##value", &value, 0.01f, -10000.0f, 10000.0f, "%.2f");
	}
	ImGui::PopID();
	return false;
}

bool Fracture::UIElement::Property(const std::string& label, glm::vec2& value, float reset_value)
{
	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 1.5f;
	ImVec2 buttonSize = { lineHeight , lineHeight };

	ImGui::PushID(EditorApplication::NextGuiID());

	ImGui::TableNextColumn();

	ImGui::Text(label.c_str());

	ImGui::TableNextColumn();
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 0,0 });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.8f,0.30f,0.30f,1.0f });
		if (ImGui::Button("X", buttonSize))
		{
			value.x = reset_value;
		}
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
		ImGui::SameLine();
		ImGui::PushItemWidth(-5);
		ImGui::DragFloat("##posx", &value.x, 0.01f, 0.0f, 100.0f, "%.2f");
	}
	ImGui::TableNextColumn();
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 0,0 });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.30f,0.8f,0.30f,1.0f });
		if (ImGui::Button("Y", buttonSize))
		{
			value.y = reset_value;
		}

		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
		ImGui::SameLine();
		ImGui::PushItemWidth(-5);
		ImGui::DragFloat("##posy", &value.y, 0.01f, 0.0f, 100.0f, "%.2f");
	}
	ImGui::PopID();
	return false;
}

bool Fracture::UIElement::Property(const std::string& label, glm::vec3& value, float reset_value)
{
	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 1.0f;
	ImVec2 buttonSize = { lineHeight + 2.0f, lineHeight };

	ImGui::PushID(EditorApplication::NextGuiID());

	ImGui::TableNextColumn();

	ImGui::Text(label.c_str());

	ImGui::TableNextColumn();
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 0,0 });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.8f,0.30f,0.30f,1.0f });
		if (ImGui::Button("X", buttonSize))
		{
			value.x = reset_value;
		}
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
		ImGui::SameLine();
		ImGui::PushItemWidth(-5);
		ImGui::DragFloat("##posx", &value.x, 0.01f, -10000.0f, 10000.0f, "%.2f");
	}
	ImGui::TableNextColumn();
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 0,0 });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.30f,0.8f,0.30f,1.0f });
		if (ImGui::Button("Y", buttonSize))
		{
			value.y = reset_value;
		}

		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
		ImGui::SameLine();
		ImGui::PushItemWidth(-5);
		ImGui::DragFloat("##posy", &value.y, 0.01f, -10000.0f, 10000.0f, "%.2f");

	}
	ImGui::TableNextColumn();
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 0,0 });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.30f,0.30f,0.8f,1.0f });
		if (ImGui::Button("Z", buttonSize))
		{
			value.z = reset_value;
		}
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();

		ImGui::SameLine();
		ImGui::PushItemWidth(-5);
		ImGui::DragFloat("##posz", &value.z, 0.01f, -10000.0f, 10000.0f, "%.2f");
	}

	ImGui::PopID();
	return false;

}

bool Fracture::UIElement::Property(const std::string& label, glm::vec4& value, float reset_value)
{
	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 1.5f;
	ImVec2 buttonSize = { lineHeight + 0.0f, lineHeight };

	ImGui::PushID(EditorApplication::NextGuiID());

	ImGui::TableNextColumn();

	ImGui::Text(label.c_str());

	ImGui::TableNextColumn();
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 0,0 });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.8f,0.30f,0.30f,1.0f });
		if (ImGui::Button("X", buttonSize))
		{
			value.x = reset_value;
		}
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
		ImGui::SameLine();
		ImGui::PushItemWidth(-5);
		ImGui::DragFloat("##posx", &value.x, 0.01f, -10000.0f, 10000.0f, "%.2f");
	}
	ImGui::TableNextColumn();
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 0,0 });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.30f,0.8f,0.30f,1.0f });
		if (ImGui::Button("Y", buttonSize))
		{
			value.y = reset_value;
		}

		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
		ImGui::SameLine();
		ImGui::PushItemWidth(-5);
		ImGui::DragFloat("##posy", &value.y, 0.01f, -10000.0f, 10000.0f, "%.2f");

	}
	ImGui::TableNextColumn();
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 0,0 });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.30f,0.30f,0.8f,1.0f });
		if (ImGui::Button("Z", buttonSize))
		{
			value.z = reset_value;
		}
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();

		ImGui::SameLine();
		ImGui::PushItemWidth(-5);
		ImGui::DragFloat("##posz", &value.z, 0.01f, -10000.0f, 10000.0f, "%.2f");
	}
	ImGui::TableNextColumn();
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 0,0 });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.30f,0.30f,0.8f,1.0f });
		if (ImGui::Button("W", buttonSize))
		{
			value.w = reset_value;
		}
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();

		ImGui::SameLine();
		ImGui::PushItemWidth(-5);
		ImGui::DragFloat("##posw", &value.w, 0.01f, 0.0f, 100.0f, "%.2f");
	}

	ImGui::PopID();
	return false;
}

bool Fracture::UIElement::ColorProperty(const std::string& label, glm::vec3& value, float reset_value)
{
	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 1.5f;
	ImVec2 buttonSize = { lineHeight + 0.0f, lineHeight };

	ImGui::PushID(EditorApplication::NextGuiID());

	ImGui::TableNextColumn();

	ImGui::Text(label.c_str());

	ImGui::TableNextColumn();
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 0,0 });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.8f,0.30f,0.30f,1.0f });
		if (ImGui::Button("-", buttonSize))
		{
			value = glm::vec3(1.0f);
		}
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
		ImGui::SameLine();
		ImGui::PushItemWidth(-5);
		float col[3] = { value.x,value.y,value.z };

		ImGui::PushItemWidth(32);
		ImGuiColorEditFlags flag = ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs ;
		if (ImGui::ColorPicker3("##color", col,flag))
		{
			value = glm::vec3(col[0], col[1], col[2]);
		}
		ImGui::PopItemWidth();
	}
	ImGui::PopID();

	return false;
}

bool Fracture::UIElement::ColorProperty(const std::string& label, glm::vec4& value, float reset_value)
{
	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 1.5f;
	ImVec2 buttonSize = { lineHeight + 0.0f, lineHeight };

	ImGui::PushID(EditorApplication::NextGuiID());

	ImGui::TableNextColumn();

	ImGui::Text(label.c_str());

	ImGui::TableNextColumn();
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 0,0 });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.8f,0.30f,0.30f,1.0f });
		if (ImGui::Button("-", buttonSize))
		{
			value = glm::vec4(1.0f);
		}
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
		ImGui::SameLine();
		ImGui::PushItemWidth(-5);
		float col[4] = {value.x,value.y,value.z,value.w };

		if (ImGui::ColorEdit4("##col4",col, 0))
		{
			value = glm::vec4(col[0], col[1], col[2], col[3]);
		}
	}
	ImGui::PopID();

	return false;
}
