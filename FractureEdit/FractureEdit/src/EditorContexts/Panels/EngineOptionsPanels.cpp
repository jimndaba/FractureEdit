#include "EdPCH.h"
#include "EngineOptionsPanels.h"
#include "core/Components.h"

Fracture::CameraOptions::CameraOptions(CameraComponent* component):camera(component)
{
}

void Fracture::CameraOptions::OnRender(bool* p_open)
{
	BeginProps(2);
	Property("Speed", camera->Speed);
	Property("Damping", camera->Damping);
	Property("Sensitivity", camera->Sensitivity);
	EndProps();
}
