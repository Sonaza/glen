#include <glen/Graphics/Texture/Texture.hpp>

using namespace glen;

////////////////////////////////////////////////////
Texture::Texture() :
	m_loaded(false),
	m_textureId(0)
{
	
}

////////////////////////////////////////////////////
Texture::~Texture()
{
	if(m_textureId != 0)
	{
		glDeleteTextures(1, &m_textureId);
	}
}

/////////////////////////////////////////////////
void Texture::setClamping(const Clamping value)
{
	bind();

	m_settings.clamping = value;

	switch(m_settings.clamping)
	{
	case Clamp:
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		break;
	case Repeat:
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		break;
	}
}

/////////////////////////////////////////////////
void Texture::setFiltering(const Filtering value)
{
	bind();

	m_settings.filtering = value;

	switch(m_settings.filtering)
	{
	case Linear:
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case Nearest:
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	}
}

/////////////////////////////////////////////////
void Texture::setAnisotropy(const uint32 value)
{
	bind();

	m_settings.anisotropy = value;
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, static_cast<GLfloat>(value));
}
