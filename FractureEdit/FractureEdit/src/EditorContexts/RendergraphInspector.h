#pragma once
#ifndef GRAPHINSPECTOR_H
#define GRAPHINSPECTOR_H

#include "EditingContext.h"

#include "Panels/UIElement.h"
#include "Panels/RendergraphPanel.h"

namespace Fracture
{
	class RenderGraphInspector : public EditingContext
	{
	public:
		RenderGraphInspector();

		void OnUpdate();
		void OnRender(bool* p_open, Device* device);

		void OnSetRenderGraph(const std::shared_ptr<SetRenderGraph>& evnt);

		std::vector<std::shared_ptr<UIElement>> mElements;

	};
}




#endif
