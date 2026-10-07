#pragma once

#include <glm/glm.hpp>

struct CameraComponent
{
	bool costrainPitch = true;
	float pitchAngle = 0.0f;
	float yawAngle = -90.0f;
	float FOV = 45.0f;

	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	float nearPlane = 0.1f;
	float farPlane = 100.0f;
};