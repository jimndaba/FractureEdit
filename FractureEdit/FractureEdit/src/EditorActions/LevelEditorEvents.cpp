#include "EdPCH.h"
#include "LevelEditorEvents.h"

Fracture::SubmitEntityForEdit::SubmitEntityForEdit(const UUID& entity):
    Entity(entity)
{
}

bool Fracture::SubmitEntityForEdit::Handled()
{
    return true;
}

Fracture::ReleaseEntityFromEdit::ReleaseEntityFromEdit(const UUID& entity):Entity(entity)
{
}

bool Fracture::ReleaseEntityFromEdit::Handled()
{
    return false;
}
