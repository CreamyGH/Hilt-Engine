#include "Renderer.h"


Renderer::Renderer(int screenWidth, int screenHeight)
    : m_CamSystem(screenWidth, screenHeight)
{

}

void Renderer::RenderFrame(entt::registry& registry)
{
    Update(registry);
    DrawFrame(registry);
}

glm::mat4 Renderer::GetPVM_Matrix(const TransformComponent* transform)
{
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    if (transform) 
    {
        modelMatrix = transform->matrix;
    }

    return m_CamSystem.GetProjViewMatrix() * modelMatrix;
}

void Renderer::Update(entt::registry& registry)
{
    m_CamSystem.Update(registry);
}

void Renderer::ClearScreen(const glm::vec3 color)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(color.x, color.y, color.z, 1.0f);
}

void Renderer::DrawFrame(entt::registry& registry)
{
    ClearScreen({ 0.1f, 0.1f, 0.1f });

    auto view = registry.view<RenderComponent>();

    for (auto entity : view)
    {
        RenderComponent& renderComp = view.get<RenderComponent>(entity);

        Shader* currentShader = renderComp.material->GetShader();

        if (!currentShader)
            continue;

        currentShader->UseProgram();

        const TransformComponent* transform = registry.try_get<TransformComponent>(entity);

        glm::mat4 PVM_matrix = GetPVM_Matrix(transform);

        currentShader->SetMat4("PVM", PVM_matrix);

        renderComp.material->Bind();
        renderComp.mesh->Bind();

        GLsizei indicesCount = static_cast<GLsizei>(renderComp.mesh->GetIndices().size());

        glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr);

        renderComp.mesh->UnBind();
    }
}