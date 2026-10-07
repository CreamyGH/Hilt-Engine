#pragma once

#include <entt/entt.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

#include "../Components/TransformComponent.h"

class TransformSystem
{
public:
    void Update(entt::registry& registry);
};