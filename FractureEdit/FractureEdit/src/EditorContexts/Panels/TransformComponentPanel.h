#pragma once
#ifndef TRANSFORMPANEL_H
#define TRANSFORMPANEL_H


namespace Fracture
{
	struct TransfromComponentPanel
	{
		TransfromComponentPanel();
		void OnRender(bool* p_open);
		//TransformComponent* component;

		bool Property(const std::string& label, glm::vec3& value, float reset_value = 0);

	};



}

#endif