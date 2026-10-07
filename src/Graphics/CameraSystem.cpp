#include "CameraSystem.h"

CameraSystem::CameraSystem(int screenWidth, int screenHeight)
	: m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight)
{

}

void CameraSystem::Update(entt::registry& registry)
{
	if (m_CameraEntity == entt::null) {
		std::cout << "There is no active camera!" << '\n';
		return;
	}

	CameraComponent* cam = registry.try_get<CameraComponent>(m_CameraEntity);
	TransformComponent* transform = registry.try_get<TransformComponent>(m_CameraEntity);

	if (!cam)
	{
		std::cout << "There is no camera attached to entity" << '\n';
		return;
	}

	if (transform) 
	{
		m_Pos = transform->position;
	}

	m_FOV = cam->FOV;
	m_MinProjectionDist = cam->nearPlane;
	m_MaxProjectionDist = cam->farPlane;

	m_Pitch = cam->pitchAngle;
	m_Yaw = cam->yawAngle;

	if (cam->costrainPitch)
	{
		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;

		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;
	}

	RotateEuler();
	CalculateCamRight();

	cam->front = m_CamFront;
	cam->right = m_CamRight;
	cam->up = m_CamUp;

	m_ViewMat = glm::lookAt(m_Pos, m_Pos + m_CamFront, m_CamUp);
	m_ProjectionMat = glm::perspective(glm::radians(m_FOV), (float)m_ScreenWidth / (float)m_ScreenHeight, m_MinProjectionDist, m_MaxProjectionDist);
}

void CameraSystem::CalculateCamRight()
{
	m_CamRight = glm::normalize(glm::cross(m_CamFront, m_CamUp));
}

void CameraSystem::RotateEuler()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	direction.y = sin(glm::radians(m_Pitch));
	direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_CamFront = glm::normalize(direction);
}