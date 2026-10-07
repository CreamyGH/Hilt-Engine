#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Components/CameraComponent.h"
#include "../Components/TransformComponent.h"

#include <entt/entt.hpp>

class CameraSystem
{
public:
	CameraSystem(int screenWidth, int screenHeight);
	void SetCameraEntity(const entt::entity entity) { m_CameraEntity = entity; }

	void Update(entt::registry& registry);

	glm::mat4 GetProjViewMatrix() { return m_ProjectionMat * m_ViewMat; }

private:
	void RotateEuler();
	void CalculateCamRight();

private:
	entt::entity m_CameraEntity = entt::null;

	glm::mat4 m_ViewMat = glm::mat4(1.0f);
	glm::mat4 m_ProjectionMat = glm::mat4(1.0f);

	glm::vec3 m_Pos = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 m_CamFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_CamRight = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 m_CamUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float m_FOV = 45.0f;
	float m_MinProjectionDist = 0.1f;
	float m_MaxProjectionDist = 100.0f;

	int m_ScreenWidth = 0, m_ScreenHeight = 0;

	float m_Pitch = 0.0f, m_Yaw = -90.0f;
};