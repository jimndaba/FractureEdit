#pragma once
#ifndef ASSETMANAGER_H
#define ASSETMAANGER_H



#include "EditingContext.h"

namespace Fracture
{
	class AssetManagerContext : public EditingContext
	{
	public:
		AssetManagerContext();

		void OnRender(bool* p_open);


	};
}


#endif