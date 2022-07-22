#pragma once
#ifndef ENTITYINSPECTOR_H
#define ENTITYINSPECTOR_H

#include "EditingContext.h"

#include "Panels/TransformComponentPanel.h"

namespace Fracture
{
	class Inspector : public EditingContext
	{
	public:
		Inspector();
		void OnUpdate();
		void OnRender(bool* p_open, Device* device);

		std::unique_ptr<TransfromComponentPanel> mTranfoms;

	};
}




#endif