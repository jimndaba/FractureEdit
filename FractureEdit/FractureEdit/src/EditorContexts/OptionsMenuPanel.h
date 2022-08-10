#pragma once
#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include "EditingContext.h"

namespace Fracture
{
	struct CameraOptions;
	struct ProjectOptions;

	class EngineOpitonsContext : public EditingContext
	{		
	public:
		EngineOpitonsContext();
		void OnInit();
		void OnUpdate();
		void OnRender(bool* p_open, Device* device);

		std::shared_ptr<CameraOptions> mCameraOptions;
		std::shared_ptr<ProjectOptions> mProjectOptions;
	};

}

#endif