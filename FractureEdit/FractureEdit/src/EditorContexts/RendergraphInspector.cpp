#include "EdPCH.h"
#include "RendergraphInspector.h"
#include "rendering/RenderGraph.h"



Fracture::RenderGraphInspector::RenderGraphInspector()
{
}

void Fracture::RenderGraphInspector::OnUpdate()
{

}

void Fracture::RenderGraphInspector::OnRender(bool* p_open, Device* device)
{
	ImGui::Begin("RenderGraph Inspector");
	for (const auto& panel : mElements)
	{
		panel->OnRender(p_open);
	}
	ImGui::End();
}

void Fracture::RenderGraphInspector::OnSetRenderGraph(const std::shared_ptr<SetRenderGraph>& evnt)
{
	mElements.clear();

	for (const auto& node : evnt->Graph.m_FrameNodeQueue)
	{
		if ((std::dynamic_pointer_cast<SSAONode>(node)))
		{
			const auto& pass = std::dynamic_pointer_cast<SSAONode>(node);
			mElements.push_back(std::make_shared<SSAOPanel>(pass.get()));
		}

		if ((std::dynamic_pointer_cast<GlobalAmbientLightNode>(node)))
		{
			const auto& pass = std::dynamic_pointer_cast<GlobalAmbientLightNode>(node);
			mElements.push_back(std::make_shared<IBLPanel>(pass.get()));
		}

		if ((std::dynamic_pointer_cast<BloomNode>(node)))
		{
			const auto& pass = std::dynamic_pointer_cast<BloomNode>(node);
			mElements.push_back(std::make_shared<BloomPanel>(pass.get()));
		}

		if ((std::dynamic_pointer_cast<ChromaticAberrationNode>(node)))
		{
			const auto& pass = std::dynamic_pointer_cast<ChromaticAberrationNode>(node);
			mElements.push_back(std::make_shared<ChromaticAberrationPanel>(pass.get()));
		}

		if ((std::dynamic_pointer_cast<VignetteNode>(node)))
		{
			const auto& pass = std::dynamic_pointer_cast<VignetteNode>(node);
			mElements.push_back(std::make_shared<VignettePanel>(pass.get()));
		}

		if ((std::dynamic_pointer_cast<FXAANode>(node)))
		{
			const auto& pass = std::dynamic_pointer_cast<FXAANode>(node);
			mElements.push_back(std::make_shared<FXAAPanel>(pass.get()));
		}

		if ((std::dynamic_pointer_cast<ToneMappingNode>(node)))
		{
			const auto& pass = std::dynamic_pointer_cast<ToneMappingNode>(node);
			mElements.push_back(std::make_shared<ToneMappingPanel>(pass.get()));
		}

		if ((std::dynamic_pointer_cast<SSRNode>(node)))
		{
			const auto& pass = std::dynamic_pointer_cast<SSRNode>(node);
			mElements.push_back(std::make_shared<SSRPanel>(pass.get()));
		}

		if ((std::dynamic_pointer_cast<DepthOfFieldNode>(node)))
		{
			const auto& pass = std::dynamic_pointer_cast<DepthOfFieldNode>(node);
			mElements.push_back(std::make_shared<DepthOfFieldPanel>(pass.get()));
		}


		if ((std::dynamic_pointer_cast<SunShadowNode>(node)))
		{
			const auto& pass = std::dynamic_pointer_cast<SunShadowNode>(node);
			mElements.push_back(std::make_shared<DirectShadowsPanel>(pass.get()));
		}

	}

}
