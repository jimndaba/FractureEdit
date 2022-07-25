#pragma once
#ifndef EDITINGCONTEXT_H
#define EDITINGCONTEXT_H

#include "core/Components.h"
#include "rendering/Device.h"
#include "rendering/DeviceContext.h"


#include "EditorActions/LevelEditorEvents.h"

namespace Fracture
{

	class EditingContext
	{
	public:
		EditingContext();
		virtual void OnUpdate() = 0;
		virtual void OnRender(bool* p_open, Device* device) = 0;

		virtual void OnSetScene(const std::shared_ptr<SetSceneForEditing>& evnt);
		virtual void OnSubmitEntityForEdit(const std::shared_ptr<SubmitEntityForEdit>& evnt);
		virtual void OnReleaseEntityFromEdit(const std::shared_ptr<ReleaseEntityFromEdit>& evnt);	
	};	
}

#endif

