#pragma once
#ifndef LEVELEDITORACTIONS_H
#define LEVELEDITORACTIONS_H

#include "events/Event.h"

namespace Fracture
{
	class Scene;

	struct SubmitEntityForEdit : public Event
	{
		SubmitEntityForEdit(const UUID& entity);
		bool Handled();
		UUID Entity;
	};

	struct ReleaseEntityFromEdit : public Event
	{
		ReleaseEntityFromEdit(const UUID& entity);
		bool Handled();
		UUID Entity;
	};

	struct SetSceneForEditing : public Event
	{
		SetSceneForEditing(Scene& s);
		bool Handled();
		Scene& scene;
	};
}

#endif