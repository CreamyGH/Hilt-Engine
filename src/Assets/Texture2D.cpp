#define STB_IMAGE_IMPLEMENTATION
#include "Texture2D.h"

void Texture2D::CreateGLTexture()
{
	glGenTextures(1, &m_TextureID);
}

void Texture2D::LoadFromImage(const char* imagePath, bool flipVertically)
{
	m_Data.path = imagePath;

	stbi_set_flip_vertically_on_load(flipVertically);
	unsigned char* data = stbi_load(imagePath, &m_Data.width, &m_Data.height, &m_Data.nrChannels, 0);

	if (!data)
	{
		std::cout << "Failed to load texture from path: " << imagePath << '\n';
		return;
	}

	std::size_t dataSize = static_cast<std::size_t>(m_Data.width) *
		static_cast<std::size_t>(m_Data.height) *
		static_cast<std::size_t>(m_Data.nrChannels);

	m_Data.pixels.assign(data, data + dataSize);

	stbi_image_free(data);
}

void Texture2D::Create()
{
	CreateGLTexture();
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	SetParameters();
	UploadData();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind(uint32_t slot)
{
	glActiveTexture(GL_TEXTURE0 + m_Slot);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture2D::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::SetParameters()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture2D::UploadData()
{
	if (m_Data.pixels.empty()) {
		std::cout << "Pixel data in path: " << m_Data.path << "is empty";
		return;
	}

	if (m_Data.nrChannels == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_Data.width, m_Data.height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_Data.pixels.data());

	if (m_Data.nrChannels == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Data.width, m_Data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Data.pixels.data());

	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture2D::DeleteGLTexture()
{
	glDeleteTextures(1, &m_TextureID);
}

Texture2D::~Texture2D()
{
	DeleteGLTexture();
}