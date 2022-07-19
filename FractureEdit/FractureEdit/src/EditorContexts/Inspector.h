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

		void OnRender(bool* p_open);

		std::unique_ptr<TransfromComponentPanel> mTranfoms;

	};
}




#endif