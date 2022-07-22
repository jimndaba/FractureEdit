#pragma once
#ifndef EDITINGCONTEXT_H
#define EDITINGCONTEXT_H

#include "core/Components.h"
#include "rendering/Device.h"
#include "rendering/DeviceContext.h"

namespace Fracture
{

	class EditingContext
	{
	public:
		virtual void OnUpdate() = 0;
		virtual void OnRender(bool* p_open, Device* device) = 0;
	};




}

#endif

