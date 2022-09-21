#include "EdPCH.h"
#include "InspectorPanels.h"
#include "core/Components.h"
#include "EditorApplication.h"
#include "core/Entity.h"
#include "rendering/StaticMesh.h"

Fracture::TransfromComponentPanel::TransfromComponentPanel(TransformComponent* transform):
	component(transform)
{
}

void Fracture::TransfromComponentPanel::OnRender(bool* p_open)
{
	float button_size = 100;
	ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_DefaultOpen;

	ImGui::PushID(EditorApplication::NextGuiID());
	bool open = ImGui::TreeNodeEx("Transform", tree_flags);
	if (open)
	{		
		BeginProps(4);
		Property("Position", component->Position);
		Property("Scale", component->Scale);
		Property("Rotation ", component->Rotation);
		EndProps();

		ImGui::TreePop();
	}
	ImGui::PopID();
}

Fracture::TagComponentPanel::TagComponentPanel(TagComponent* tag):component(tag)
{
}

void Fracture::TagComponentPanel::OnRender(bool* p_open)
{
	float button_size = 100;
	ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_DefaultOpen;
	ImGui::PushID(EditorApplication::NextGuiID());

	bool open = ImGui::TreeNodeEx("Tag", tree_flags);
	if (open)
	{
		ImGuiTableFlags flags = ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersH;

		BeginProps(2);
		PropertyEx("Name", component->Name);
		Property("UUID", std::to_string(component->ID));
		EndProps();
		ImGui::TreePop();
	}
	ImGui::PopID();
}

Fracture::PointlightPanel::PointlightPanel(PointlightComponent* light):
	component(light)
{
}

void Fracture::PointlightPanel::OnRender(bool* p_open)
{
	float button_size = 100;
	ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_DefaultOpen;
	ImGui::PushID(EditorApplication::NextGuiID());
	bool open = ImGui::TreeNodeEx("Pointlight", tree_flags);
	if (open)
	{
		BeginProps(2);
		Property("Radius", component->Radius);
		Property("Compression", component->Compression);
		Property("Intensity", component->Intensity);
		ColorProperty("Diffuse", component->Diffuse);
		ColorProperty("Specular", component->Specular);
		EndProps();
		ImGui::TreePop();
	}
	ImGui::PopID();
}

Fracture::CameraComponentPanel::CameraComponentPanel(CameraComponent* camera):component(camera)
{
}

void Fracture::CameraComponentPanel::OnRender(bool* p_open)
{
	float button_size = 100;
	ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_DefaultOpen;
	ImGui::PushID(EditorApplication::NextGuiID());
	bool open = ImGui::TreeNodeEx("Pointlight", tree_flags);
	if (open)
	{
		BeginProps(4);
		Property("Position", component->TargetPosition);
		Property("Up", component->Up);
		Property("Right", component->Right);
		EndProps();

		BeginProps(2);
		Property("FoV", component->TargetFoV);
		Property("Near", component->Near);
		Property("Far", component->Far);	
		Property("Pitch", component->TargetPitch);
		Property("Roll", component->TargetRoll);
		Property("Yaw", component->TargetYaw);
		EndProps();
		
		BeginProps(2);
		Property("Speed", component->Speed);
		Property("Sensitivity", component->Sensitivity);
		Property("Damping", component->Damping);
		EndProps();

		BeginProps(2);
		Property("Enable Depth of Field", &component->EnableDepthOfField);
		if (component->EnableDepthOfField)
		{
			Property("Focal Range", component->FocalRange);
			Property("Focal Length", component->FocalLength);
		}
		EndProps();


		ImGui::TreePop();
	}
	ImGui::PopID();
}

Fracture::StaticMeshComponentPanel::StaticMeshComponentPanel(StaticMeshComponent* mesh):component(mesh)
{
}

void Fracture::StaticMeshComponentPanel::OnAttach()
{
	blank_texture = AssetManager::GetTextureByName("Blank_Texture")->RenderID;
}

void Fracture::StaticMeshComponentPanel::OnRender(bool* p_open)
{
	float button_size = 100;
	ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_DefaultOpen;
	ImGui::PushID(EditorApplication::NextGuiID());
	bool open = ImGui::TreeNodeEx("StaticMesh", tree_flags);
	if (open)
	{
		BeginProps(2);
		PropertyEx("Mesh", component->Mesh->Name);
		Property("Override Material", &component->OverrideMeshMaterial);
		EndProps();

		if (component->OverrideMeshMaterial)
		{
			const auto& mat = AssetManager::GetMaterialbyID(component->MaterialID);			
			if (mat)
			{
				const ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
				int matID = EditorApplication::NextGuiID();
				ImGui::PushID(matID);
				bool openMat = ImGui::TreeNodeEx((void*)matID, flags, mat->Name.c_str());
				if (openMat)
				{
					BeginProps(2);
					Property("Casts shadows?", &mat->CastsShadows);
					Property("Is Translucent", &mat->IsTranslucent);
					Property("Is Tiled", &mat->IsTiledTextures);
					if (mat->IsTiledTextures)
					{
						Property("Tiling Scale", mat->TilingScale);
					}
					ColorProperty("Diffuse", mat->Diffuse);
					ColorProperty("Emission", mat->Emmision);
					ColorProperty("Specular", mat->Specular);
					Property("Metallic", mat->Metalic, 0.0f);
					Property("Roughness", mat->Roughness, 0.1f);
					Property("AO", mat->AO, 0.0f);
					EndProps();

					ImGui::TreePop();
				}
				ImGui::PopID();
			}
		}
		else
		{
			for (const auto& mat_id : component->Mesh->Materials)
			{
				const auto& mat = AssetManager::GetMaterialbyID(mat_id);
				const ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

				int matID = EditorApplication::NextGuiID();
				ImGui::PushID(matID);
				bool openMat = ImGui::TreeNodeEx((void*)matID, flags, mat->Name.c_str());
				if (openMat)
				{
					BeginProps(2);
					Property("Casts shadows?", &mat->CastsShadows);
					Property("Is Translucent", &mat->IsTranslucent);
					Property("Is Tiled", &mat->IsTiledTextures);
				
					if (mat->IsTiledTextures)
					{
						Property("Tiling Scale", mat->TilingScale);
					}


					uint32_t Diffuse_Texture = AssetManager::GetTextureByName("Blank_Texture")->RenderID;
					uint32_t Specular_Texture = AssetManager::GetTextureByName("Blank_Texture")->RenderID;
					uint32_t Metallice_Texture = AssetManager::GetTextureByName("Blank_Texture")->RenderID;
					uint32_t Roughness_Texture = AssetManager::GetTextureByName("Blank_Texture")->RenderID;
					uint32_t AO_Texture = AssetManager::GetTextureByName("Blank_Texture")->RenderID;

					if (mat->HasDiffuseTexture)
					{
						Diffuse_Texture = AssetManager::GetTextureByID(mat->Textures[DIFFUSE_TEXTURE])->RenderID;
					}
					if (mat->HasMetalicTexture)
					{
						Metallice_Texture = AssetManager::GetTextureByID(mat->Textures[METAL_TEXTURE])->RenderID;
					}
					if (mat->HasRoughnessTexture)
					{
						Roughness_Texture = AssetManager::GetTextureByID(mat->Textures[ROUGH_TEXTURE])->RenderID;
					}
					if (mat->HasAOTexture)
					{
						AO_Texture = AssetManager::GetTextureByID(mat->Textures[AO_TEXTURE])->RenderID;
					}
									
					PropertyImgEx("Diffuse", Diffuse_Texture, mat->Diffuse);
					PropertyImgEx("Metallic", Metallice_Texture, mat->Metalic);
					PropertyImgEx("Roughness", Roughness_Texture, mat->Roughness);
					PropertyImgEx("Ambient Occlusion", AO_Texture, mat->AO);
					ColorProperty("Specular", mat->Specular);
					EndProps();

					if (mat->Uniforms.size())
					{
						BeginProps(2);
						for (auto& uniform : mat->Uniforms)
						{
							switch (uniform.type)
							{
							case UniformType::BOOL:
							{
								Property(uniform.Name, &uniform.Data.BOOL);
								break;
							}
							case UniformType::INT:
							{
								Property(uniform.Name, uniform.Data.INT);
								break;
							}
							case UniformType::FLOAT:
							{
								Property(uniform.Name, uniform.Data.FLOAT);
								break;
							}
							case UniformType::VEC2:
							{
								Property(uniform.Name, uniform.Data.VEC2);
								break;
							}
							case UniformType::VEC3:
							{
								Property(uniform.Name, uniform.Data.VEC3);
								break;
							}
							case UniformType::VEC4:
							{
								Property(uniform.Name, uniform.Data.VEC4);
								break;
							}
							case UniformType::COLOR3:
							{
								ColorProperty(uniform.Name, uniform.Data.VEC4);
								break;
							}
							case UniformType::COLOR4:
							{
								ColorProperty(uniform.Name, uniform.Data.VEC4);
								break;
							}
							}

						}
						EndProps();
					}
					ImGui::TreePop();
				}
				ImGui::PopID();
			}
		}

		ImGui::TreePop();

	}
	ImGui::PopID();
}

Fracture::RigidbodyComponentPanel::RigidbodyComponentPanel(RigidBodyComponent* rigidbody):component(rigidbody)
{
}

void Fracture::RigidbodyComponentPanel::OnAttach()
{
}

void Fracture::RigidbodyComponentPanel::OnRender(bool* p_open)
{
	float button_size = 100;
	ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_DefaultOpen;
	ImGui::PushID(EditorApplication::NextGuiID());
	bool open = ImGui::TreeNodeEx("RigidBody", tree_flags);
	if (open)
	{
		BeginProps(2);
		Property("Angular Drag", component->AngularDrag);
		Property("Linear Drag", component->LinearDrag);
		Property("Mass", component->Mass);
		Property("Is Kinematic", &component->isKinematic);
		//ColorProperty("Diffuse", component->Diffuse);
		//ColorProperty("Specular", component->Specular);
		EndProps();
		ImGui::TreePop();
	}
	ImGui::PopID();
}

Fracture::ColliderComponentPanel::ColliderComponentPanel(ColliderComponent* collider):component(collider)
{
}

void Fracture::ColliderComponentPanel::OnAttach()
{
}

void Fracture::ColliderComponentPanel::OnRender(bool* p_open)
{
	float button_size = 100;
	ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_DefaultOpen;
	ImGui::PushID(EditorApplication::NextGuiID());
	bool open = ImGui::TreeNodeEx("Collider", tree_flags);
	if (open)
	{
		BeginProps(2);
		Property("Height", component->mHeight);
		Property("Offset", component->mOffset);
		Property("Radius", component->mRadius);
		ColorProperty("Size", component->mSize);
		EndProps();
		ImGui::TreePop();
	}
	ImGui::PopID();
}
