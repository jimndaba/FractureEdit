#pragma once
#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include "EditingContext.h"

namespace Fracture
{
	struct CameraOptions;

	class EngineOpitonsContext : public EditingContext
	{
		std::shared_ptr<CameraOptions> mCameraOptions;

	public:
		EngineOpitonsContext();
		void OnInit();
		void OnUpdate();
		void OnRender(bool* p_open, Device* device);
	};

}

#endif