#pragma once

#include <memory>

#include "Shader.h"
#include "Texture2D.h"

class Material
{
public:
	void SetShader(std::shared_ptr<Shader> shader) { m_Shader = shader; }
	void SetTexture(std::shared_ptr<Texture2D> texture) { m_Texture = texture; }
	Shader* GetShader() { return m_Shader.get(); }

	void Bind();
private:
	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<Texture2D> m_Texture;
};