#include "EdPCH.h"
#include "RendergraphPanel.h"
#include "EditorApplication.h"

Fracture::ToneMappingMode IntToTonemap(const int& value)
{
	if (value == 0) return Fracture::ToneMappingMode::HDR;
	if (value == 1) return Fracture::ToneMappingMode::Uncharted2v1;
	if (value == 2) return Fracture::ToneMappingMode::Uncharted2v2;
	if (value == 3) return Fracture::ToneMappingMode::Filmic;
	if (value == 4) return Fracture::ToneMappingMode::ACES;
	if (value == 5) return Fracture::ToneMappingMode::Reinhard;
}

Fracture::MixMode IntToMixMode(const int& value)
{
	if (value == 0) return Fracture::MixMode::Add;
	if (value == 1) return Fracture::MixMode::Multiply;
	if (value == 2) return Fracture::MixMode::Subtract;
	if (value == 3) return Fracture::MixMode::Divide;
	if (value == 4) return Fracture::MixMode::Darken;
	if (value == 5) return Fracture::MixMode::Lighten;
	if (value == 6) return Fracture::MixMode::Dodge;
	if (value == 7) return Fracture::MixMode::Burn;
}


Fracture::BloomPanel::BloomPanel(BloomNode* node):Node(node)
{
}

void Fracture::BloomPanel::OnRender(bool* p_open)
{
	float button_size = 100;
	ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_DefaultOpen;

	ImGui::PushID(EditorApplication::NextGuiID());
	bool open = ImGui::TreeNodeEx("Bloom", tree_flags);
	if (open)
	{
		BeginProps(2);
		Property("Use Bright Pass", &Node->Properties.UseBrightPass);
		Property("Threshold", Node->Properties.Threshold);
		Property("Bloom Strength", Node->Properties.bloomStrength);
		Property("Dirt Strength", Node->Properties.DirtStrength);
		Property("Emission Strength", Node->Properties.EmissionStrength);
		Property("Radius", Node->Properties.FilterRadius);		
		EndProps();

		ImGui::TreePop();
	}
	ImGui::PopID();
}

Fracture::SSAOPanel::SSAOPanel(SSAONode* node) :Node(node)
{
	
}

void Fracture::SSAOPanel::OnRender(bool* p_open)
{
	float button_size = 100;
	ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_DefaultOpen;
	ImGui::PushID(EditorApplication::NextGuiID());
	bool open = ImGui::TreeNodeEx("SSAO", tree_flags);
	if (open)
	{
		BeginProps(2);
		Property("Strength", Node->Properties.strength);
		Property("Radius", Node->Properties.radius);
		Property("No. Samples", Node->Properties.NoSamples);
		Property("Falloff", Node->Properties.falloff);
		Property("Blur Size", Node->Properties.BlurSize);
		Property("Base", Node->Properties.base);
		Property("Area", Node->Properties.area);
		EndProps();
		ImGui::TreePop();
	}
	ImGui::PopID();
}

Fracture::DirectShadowsPanel::DirectShadowsPanel(SunShadowNode* node) :Node(node)
{
}

void Fracture::DirectShadowsPanel::OnRender(bool* p_open)
{
	float button_size = 100;
	ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_DefaultOpen;
	ImGui::PushID(EditorApplication::NextGuiID());
	bool open = ImGui::TreeNodeEx("Shadows", tree_flags);
	if (open)
	{
		BeginProps(2);
		Property("Cascades", Node->Properties.CascadeCount);
		Property("Bias", Node->Properties.Bias);		
		Property("Far Plane", Node->Properties.CameraFarPlane);		
		EndProps();
		ImGui::TreePop();
	}
	ImGui::PopID();
}

Fracture::GlobalSunPanel::GlobalSunPanel(SunlightComponent* node) :Node(node)
{
}

void Fracture::GlobalSunPanel::OnRender(bool* p_open)
{
}

Fracture::IBLPanel::IBLPanel(GlobalAmbientLightNode* node) :Node(node)
{
}

void Fracture::IBLPanel::OnRender(bool* p_open)
{
	float button_size = 100;
	ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_DefaultOpen;
	ImGui::PushID(EditorApplication::NextGuiID());
	bool open = ImGui::TreeNodeEx("IBL Properties", tree_flags);
	if (open)
	{
		BeginProps(2);		
		EndProps();
		ImGui::TreePop();
	}
	ImGui::PopID();
}

Fracture::ChromaticAberrationPanel::ChromaticAberrationPanel(ChromaticAberrationNode* node) :Node(node)
{
}

void Fracture::ChromaticAberrationPanel::OnRender(bool* p_open)
{
	float button_size = 100;
	ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_DefaultOpen;
	ImGui::PushID(EditorApplication::NextGuiID());
	bool open = ImGui::TreeNodeEx("Chromatic Aberration", tree_flags);
	if (open)
	{
		BeginProps(2);
		Property("ByPass", &Node->Properties.ByPass);
		Property("Red offset", Node->Properties.redOffset);
		Property("Green offset", Node->Properties.greenOffset);
		Property("Blue offset", Node->Properties.blueOffset);
		EndProps();
		ImGui::TreePop();
	}
	ImGui::PopID();
}

Fracture::VignettePanel::VignettePanel(VignetteNode* node) :Node(node)
{
}

void Fracture::VignettePanel::OnRender(bool* p_open)
{
	float button_size = 100;
	ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_DefaultOpen;
	ImGui::PushID(EditorApplication::NextGuiID());
	bool open = ImGui::TreeNodeEx("Vignette", tree_flags);
	if (open)
	{
		BeginProps(2);
		Property("Inner Falloff", Node->Properties.Inner);
		Property("Outer Falloff", Node->Properties.Outer);
		Property("Roundness", Node->Properties.Roundness);
		Property("Smoothness", Node->Properties.Smoothness);
		EndProps();
		ImGui::TreePop();
	}
	ImGui::PopID();
}

Fracture::FXAAPanel::FXAAPanel(FXAANode* node) :Node(node)
{
}

void Fracture::FXAAPanel::OnRender(bool* p_open)
{
	float button_size = 100;
	ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_DefaultOpen;
	ImGui::PushID(EditorApplication::NextGuiID());
	bool open = ImGui::TreeNodeEx("FXAA", tree_flags);
	if (open)
	{
		BeginProps(2);
		Property("Max Span", Node->Properties.MaxSpans);		
		EndProps();
		ImGui::TreePop();
	}
	ImGui::PopID();
}

Fracture::ToneMappingPanel::ToneMappingPanel(ToneMappingNode* node) :Node(node)
{
}

void Fracture::ToneMappingPanel::OnRender(bool* p_open)
{
	float button_size = 100;
	ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_DefaultOpen;
	ImGui::PushID(EditorApplication::NextGuiID());
	bool open = ImGui::TreeNodeEx("Tone Mapping", tree_flags);
	if (open)
	{
		BeginProps(2);
		Property("Gamma", Node->Properties.Gamma);
		Property("Exposure", Node->Properties.Exposure);
		Property("Contrast", Node->Properties.Contrast);
		Property("Brightness", Node->Properties.Brightness);

		static std::string m_types[] = {
						"HDR",
						"Uncharted2v1",
						"Uncharted2v2",
						"Filmic",
						"ACES",
						"Reinhard"
		};


		static int item_current_idx = 0;
		std::string current_type = m_types[item_current_idx];
		ImGui::PushItemWidth(-5);
		if (ImGui::BeginCombo("##tone", current_type.c_str()))
		{
			for (int n = 0; n < IM_ARRAYSIZE(m_types); n++)
			{
				const bool is_selected = (item_current_idx == n);
				if (ImGui::Selectable(m_types[n].c_str(), is_selected))
				{
					item_current_idx = n;
				}
				// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
		Node->mode = IntToTonemap(item_current_idx);

		EndProps();
		ImGui::TreePop();
	}
	ImGui::PopID();
}

Fracture::SSRPanel::SSRPanel(SSRNode* node) :Node(node)
{
}

void Fracture::SSRPanel::OnRender(bool* p_open)
{
	float button_size = 100;
	ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_DefaultOpen;
	ImGui::PushID(EditorApplication::NextGuiID());
	bool open = ImGui::TreeNodeEx("SSR", tree_flags);
	if (open)
	{
		BeginProps(2);
		
		EndProps();
		ImGui::TreePop();
	}
	ImGui::PopID();
}

Fracture::DepthOfFieldPanel::DepthOfFieldPanel(DepthOfFieldNode* node) :Node(node)
{
}

void Fracture::DepthOfFieldPanel::OnRender(bool* p_open)
{
	float button_size = 100;
	ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_DefaultOpen;
	ImGui::PushID(EditorApplication::NextGuiID());
	bool open = ImGui::TreeNodeEx("Depth of field", tree_flags);
	if (open)
	{
		BeginProps(2);
		Property("Bokeh Size", Node->Properties.BokehRadius);		
		EndProps();
		ImGui::TreePop();
	}
	ImGui::PopID();
}
