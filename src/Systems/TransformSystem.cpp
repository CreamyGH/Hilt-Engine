#include "TransformSystem.h"

void TransformSystem::Update(entt::registry& registry)
{
    auto view = registry.view<TransformComponent>();

    for (auto entity : view)
    {
        TransformComponent& transform = view.get<TransformComponent>(entity);

        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), transform.position);
        glm::mat4 rotationMatrix = glm::mat4_cast(transform.quaternion);
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), transform.scale);

        transform.matrix = translationMatrix * rotationMatrix * scaleMatrix;
    }
}