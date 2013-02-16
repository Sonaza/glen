#include <glen/Graphics/Texture.hpp>
#include <iostream>

namespace glen
{
/////////////////////////////////////////////////
Texture::Texture(void) :
	m_texture(0)
{
}

/////////////////////////////////////////////////
Texture::~Texture(void)
{
	if(m_texture != 0)
		glDeleteTextures(1, &m_texture);
}

/////////////////////////////////////////////////
void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

/////////////////////////////////////////////////
bool Texture::loadFromFile(const std::string& path, const bool clamp)
{
	GLsizei width, height;
	GLint channels;
	uint8* data = stbi_load(path.c_str(), &width, &height, &channels, 4);

	if(!data)
	{
		std::cout << "Unable to open image: " << path << std::endl;
		return false;
	}

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glCheck(glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA,
		width, height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, data
	));

	glCheck(glGenerateMipmap(GL_TEXTURE_2D));

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if(clamp)
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16);

	stbi_image_free(data);

	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

}