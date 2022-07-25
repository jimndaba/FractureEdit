#include "EdPCH.h"
#include "EditingContext.h"
#include "../EditorApplication.h"
#include "events/Eventbus.h"

Fracture::EditingContext::EditingContext()
{
	EditorApplication::Dispatcher()->Subscribe(this, &Fracture::EditingContext::OnSetScene);
	EditorApplication::Dispatcher()->Subscribe(this, &Fracture::EditingContext::OnSubmitEntityForEdit);
	EditorApplication::Dispatcher()->Subscribe(this, &Fracture::EditingContext::OnReleaseEntityFromEdit);
}

void Fracture::EditingContext::OnSetScene(const std::shared_ptr<SetSceneForEditing>& evnt)
{
}

void Fracture::EditingContext::OnSubmitEntityForEdit(const std::shared_ptr<SubmitEntityForEdit>& evnt)
{
}

void Fracture::EditingContext::OnReleaseEntityFromEdit(const std::shared_ptr<ReleaseEntityFromEdit>& evnt)
{
}
