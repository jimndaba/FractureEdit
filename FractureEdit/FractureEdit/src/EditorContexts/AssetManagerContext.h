#pragma once
#ifndef ASSETMANAGERCONTEXT_H
#define ASSETMANAGERCONTEXT_H



#include "EditingContext.h"

namespace Fracture
{
	class AssetManagerContext : public EditingContext
	{
	public:
		AssetManagerContext();
		void OnUpdate();
		void OnRender(bool* p_open,Device* device);


	};
}


#endif