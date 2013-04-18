#include <glen/Graphics/Texture/Texture2D.hpp>

using namespace glen;

/////////////////////////////////////////////////
Texture2D::Texture2D(void) :
	m_image(NULL)
{
}

/////////////////////////////////////////////////
Texture2D::~Texture2D(void)
{
	if(m_image)
	{
		delete m_image;
		m_image = NULL;
	}
}

/////////////////////////////////////////////////
void Texture2D::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_textureId);
}

/////////////////////////////////////////////////
bool Texture2D::loadFromFile(const std::string& path)
{
	m_image = new(std::nothrow) Image;
	if(!m_image->loadFromFile(path))
	{
		return false;
	}

	glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);

	glCheck(glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA8,
		m_image->getSize().x, m_image->getSize().y,
		0, GL_RGBA, GL_UNSIGNED_BYTE, m_image->getPixels()
	));

	glCheck(glGenerateMipmap(GL_TEXTURE_2D));

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16);

	m_loaded = true;

	return true;
}
