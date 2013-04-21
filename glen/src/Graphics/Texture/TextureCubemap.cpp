#include <glen/Graphics/Texture/TextureCubemap.hpp>

using namespace glen;

////////////////////////////////////////////////////
TextureCubemap::TextureCubemap()
{
}

////////////////////////////////////////////////////
TextureCubemap::~TextureCubemap()
{
}

/////////////////////////////////////////////////
void TextureCubemap::bind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureId);
}

/////////////////////////////////////////////////
bool TextureCubemap::loadFromFile(
	const std::string& left, const std::string& right,
	const std::string& top, const std::string& bottom,
	const std::string& front, const std::string& back)
{
	// +x -x +y -y +z -z

	m_filenames.push_back(left);
	m_filenames.push_back(right);
	m_filenames.push_back(top);
	m_filenames.push_back(bottom);
	m_filenames.push_back(front);
	m_filenames.push_back(back);

	if(!_loadImages())
	{
		return false;
	}

	glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureId);

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA8, m_images[0]->getWidth(), m_images[0]->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_images[0]->getPixels());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA8, m_images[1]->getWidth(), m_images[1]->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_images[1]->getPixels());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA8, m_images[2]->getWidth(), m_images[2]->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_images[2]->getPixels());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA8, m_images[3]->getWidth(), m_images[3]->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_images[3]->getPixels());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA8, m_images[4]->getWidth(), m_images[4]->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_images[4]->getPixels());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA8, m_images[5]->getWidth(), m_images[5]->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_images[5]->getPixels());

	return true;
}

/////////////////////////////////////////////////
bool TextureCubemap::_loadImages()
{
	for(std::vector<std::string>::iterator it = m_filenames.begin(); it != m_filenames.end(); ++it)
	{
		Image* temp = new(std::nothrow) Image;
		assert(temp != NULL && "Allocation failed");

		if(!temp || !temp->loadFromFile(*it))
		{
			_freeImages();
			if(temp) delete temp;

			return false;
		}

		m_images.push_back(temp);
	}

	return true;
}

/////////////////////////////////////////////////
void TextureCubemap::_freeImages()
{
	for(std::vector<Image*>::iterator it = m_images.begin(); it != m_images.end(); ++it)
	{
		if(*it != NULL) delete *it;
	}

	m_images.clear();
}