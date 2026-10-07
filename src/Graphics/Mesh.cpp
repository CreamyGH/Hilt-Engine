#include "Mesh.h"


void Mesh::Create()
{
	assert(m_Vertices.size() != 0 && "Vertices have not been assigned!");
	assert(m_Indices.size() != 0 && "Indices have not been assigned!");

	CreateGLObjects();

	Bind();

	SetVBO();
	SetEBO();
	SetAttributePointers();

	UnBindVBO();
	UnBind();
}

void Mesh::CreateGLObjects()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
}

void Mesh::Bind()
{
	assert(m_VAO && "VAO was not created!");
	assert(m_VBO && "VBO was not created!");
	assert(m_EBO && "EBO was not created!");
	glBindVertexArray(m_VAO);
}

void Mesh::UnBind()
{
	glBindVertexArray(0);
}

void Mesh::SetAttributePointers()
{
	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	//normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	// texCoords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}

void Mesh::SetVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, (size_t)(m_Vertices.size() * sizeof(Vertex)), m_Vertices.data(), GL_STATIC_DRAW);
}

void Mesh::UnBindVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::SetEBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (size_t)(m_Indices.size() * sizeof(uint32_t)), m_Indices.data(), GL_STATIC_DRAW);
}

void Mesh::DeleteGLObjects()
{
	glDeleteBuffers(1, &m_EBO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteVertexArrays(1, &m_VAO);
}

Mesh::~Mesh()
{
	DeleteGLObjects();
}


