#pragma once
#ifndef RENDERGRAPHPANEL_H
#define RENDERGRAPHPANEL_H

#include "UIElement.h"
#include "rendering/RenderGraph.h"

namespace Fracture
{
	struct BloomPanel :public UIElement
	{
		BloomPanel(BloomNode* node);
		void OnRender(bool* p_open);
		BloomNode* Node;
	};

	struct SSAOPanel : public UIElement
	{
		SSAOPanel(SSAONode* node);
		void OnRender(bool* open);
		SSAONode* Node;
	};

	struct DirectShadowsPanel : public UIElement
	{
		DirectShadowsPanel(SunShadowNode* node);
		void OnRender(bool* open);
		SunShadowNode* Node;
	};

	struct GlobalSunPanel : public UIElement
	{
		GlobalSunPanel(SunlightComponent* node);
		void OnRender(bool* open);
		SunlightComponent* Node;
	};

	struct IBLPanel : public UIElement
	{
		IBLPanel(GlobalAmbientLightNode* node);
		void OnRender(bool* open);
		GlobalAmbientLightNode* Node;
	};

	struct ChromaticAberrationPanel : public UIElement
	{
		ChromaticAberrationPanel(ChromaticAberrationNode* node);
		void OnRender(bool* open);
		ChromaticAberrationNode* Node;
	};

	struct VignettePanel : public UIElement
	{
		VignettePanel(VignetteNode* node);
		void OnRender(bool* open);
		VignetteNode* Node;
	};


	struct FXAAPanel : public UIElement
	{
		FXAAPanel(FXAANode* node);
		void OnRender(bool* open);
		FXAANode* Node;
	};

	struct ToneMappingPanel : public UIElement
	{
		ToneMappingPanel(ToneMappingNode* node);
		void OnRender(bool* open);
		ToneMappingNode* Node;
	};

	struct SSRPanel : public UIElement
	{
		SSRPanel(SSRNode* node);
		void OnRender(bool* open);
		SSRNode* Node;
	};

	struct DepthOfFieldPanel : public UIElement
	{
		DepthOfFieldPanel(DepthOfFieldNode* node);
		void OnRender(bool* open);
		DepthOfFieldNode* Node;
	};

}

#endif