#pragma once

#include <iostream>
#include <vector>
#include <assert.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>


struct Texture2Ddata
{
	std::string path;

	int width;
	int height;
	int nrChannels;
	std::vector<unsigned char> pixels{};
};

class Texture2D
{
public:
	~Texture2D();

	void LoadFromImage(const char* imagePath, bool flipVertically = false);
	void AssignSlot(uint32_t slot) { m_Slot = slot; }
	void Create();

	void Bind(uint32_t slot);
	void UnBind();

	const GLuint GetTextureID() const { return m_TextureID; }
	const uint32_t GetSlot() const { return m_Slot; }

private:
	void CreateGLTexture();
	void DeleteGLTexture();

	void SetParameters();
	void UploadData();

private:
	GLuint m_TextureID;
	Texture2Ddata m_Data{};

	uint32_t m_Slot;
};