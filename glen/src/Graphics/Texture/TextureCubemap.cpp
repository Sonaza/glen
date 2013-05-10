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

#define setCubeImage(_direction, _image) glTexImage2D(GL_TEXTURE_CUBE_MAP_ ## _direction, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_images[_image] ? m_images[_image]->getPixels() : &nulltex[0])

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

	vec2i size = m_images[0]->getSize();
	std::vector<GLubyte*> nulltex(size.x * size.y);

	setCubeImage(POSITIVE_X, 0);
	setCubeImage(NEGATIVE_X, 1);
	setCubeImage(POSITIVE_Y, 2);
	setCubeImage(NEGATIVE_Y, 3);
	setCubeImage(POSITIVE_Z, 4);
	setCubeImage(NEGATIVE_Z, 5);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return true;
}

/////////////////////////////////////////////////
bool TextureCubemap::_loadImages()
{
	vec2i size;

	for(std::vector<std::string>::iterator it = m_filenames.begin(); it != m_filenames.end(); ++it)
	{
		Image* temp = NULL;

		if(!(*it).empty())
		{
			temp = new Image;

			if(!temp->loadFromFile(*it))
			{
				_freeImages();
				if(temp) delete temp;

				return false;
			}

			if(size.x == 0 && size.y == 0)
			{
				size = temp->getSize();
			}
			else if(size != temp->getSize())
			{
				err << "All cubemap surfaces must be the same size" << ErrorStream::error;

				_freeImages();
				if(temp) delete temp;

				return false;
			}
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