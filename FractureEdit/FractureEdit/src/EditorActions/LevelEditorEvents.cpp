#include "EdPCH.h"
#include "LevelEditorEvents.h"
#include "scene/Scene.h"

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

Fracture::SetSceneForEditing::SetSceneForEditing(Scene& s):scene(s)
{
}

bool Fracture::SetSceneForEditing::Handled()
{
    return false;
}

Fracture::SetRenderGraph::SetRenderGraph(RenderGraph& graph):Graph(graph)
{
}

bool Fracture::SetRenderGraph::Handled()
{
    return false;
}

Fracture::SaveProjectEvent::SaveProjectEvent()
{
}

bool Fracture::SaveProjectEvent::Handled()
{
    return false;
}
