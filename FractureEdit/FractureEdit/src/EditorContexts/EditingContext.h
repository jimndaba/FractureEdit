#pragma once
#ifndef EDITINGCONTEXT_H
#define EDITINGCONTEXT_H


namespace Fracture
{

	class EditingContext
	{
	public:
		virtual void OnRender(bool* p_open) = 0;
	};




}

#endif

