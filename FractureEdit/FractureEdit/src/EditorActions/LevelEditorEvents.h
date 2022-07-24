#pragma once
#ifndef LEVELEDITORACTIONS_H
#define LEVELEDITORACTIONS_H

#include "events/Event.h"

namespace Fracture
{
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
}

#endif