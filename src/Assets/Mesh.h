#pragma once

#include <vector>
#include <assert.h>

#include "../Graphics/VertexData.h"

#include <glad/glad.h>

class Mesh
{
public:
    ~Mesh();

    void SetVertices(const std::vector<Vertex>& vertices) { m_Vertices = vertices;  }
    void SetIndices(const std::vector<uint32_t>& indices) { m_Indices = indices; }
    void Create();

    const std::vector<Vertex>& GetVertices() const { return m_Vertices; }
    const std::vector<uint32_t>& GetIndices() const { return m_Indices; }

    void Bind();
    void UnBind();

private:
    void CreateGLObjects();
    void DeleteGLObjects();

    void SetVBO();
    void UnBindVBO();

    void SetAttributePointers();
    void SetEBO();

private:
    std::vector<Vertex> m_Vertices{};
    std::vector<uint32_t> m_Indices{};

    GLuint m_VBO, m_EBO, m_VAO;
};