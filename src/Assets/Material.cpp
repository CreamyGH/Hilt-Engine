#include "Material.h"

void Material::Bind()
{	
	m_Shader->SetInt("texture1", m_Texture->GetSlot());
	m_Texture->Bind(m_Texture->GetSlot());
}
