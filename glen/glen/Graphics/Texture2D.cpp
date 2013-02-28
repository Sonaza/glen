#include <glen/Graphics/Texture2D.hpp>
#include <glen/System/GlenError.hpp>

namespace glen
{
/////////////////////////////////////////////////
Texture2D::Texture2D(void) :
	m_texture(0)
{

}

/////////////////////////////////////////////////
Texture2D::~Texture2D(void)
{
	if(m_texture != 0)
		glDeleteTextures(1, &m_texture);
}

/////////////////////////////////////////////////
void Texture2D::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

/////////////////////////////////////////////////
bool Texture2D::loadFromFile(const std::string& path)
{
	GLsizei width, height;
	GLint channels;
	uint8* data = stbi_load(path.c_str(), &width, &height, &channels, 4);

	if(!data)
	{
		err << "Unable to open image: " << path << Error::error;
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
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16);

	stbi_image_free(data);

	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

/////////////////////////////////////////////////
void Texture2D::setClamping(const Settings::Clamping value)
{
	bind();

	m_settings.clamping = value;

	switch(m_settings.clamping)
	{
		case Settings::Clamp:
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		break;
		case Settings::Repeat:
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		break;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

/////////////////////////////////////////////////
void Texture2D::setFiltering(const Settings::Filtering value)
{
	bind();

	m_settings.filtering = value;

	switch(m_settings.filtering)
	{
		case Settings::Linear:
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
		case Settings::Nearest:
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

}