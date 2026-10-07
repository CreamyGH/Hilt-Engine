#pragma once

#include <entt/entt.hpp>

#include "../Graphics/Shader.h"
#include "../Graphics/Mesh.h"
#include "../Graphics/Texture2D.h"
#include "../Graphics/CameraSystem.h"

#include "../Components/RenderComponent.h"

class Renderer
{
public:
	Renderer(int screenWidth, int screenHeight);
	void SetCameraEntity(entt::entity cameraEntity) { m_CamSystem.SetCameraEntity(cameraEntity); }

	void RenderFrame(entt::registry& registry);

private:
	void ClearScreen(const glm::vec3 color);
	void Update(entt::registry& registry);
	void DrawFrame(entt::registry& registry);
	glm::mat4 GetPVM_Matrix(const TransformComponent* transform);



private:
	CameraSystem m_CamSystem;
};