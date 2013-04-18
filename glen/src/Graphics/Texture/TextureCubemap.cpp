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

	std::vector<std::string> files;
	files.push_back(left);
	files.push_back(right);
	files.push_back(top);
	files.push_back(bottom);
	files.push_back(front);
	files.push_back(back);

	for(std::vector<std::string>::iterator it = files.begin(); it != files.end(); ++it)
	{
		Image* temp = new Image;
		if(!temp->loadFromFile(*it))
		{
			//m_images.
			//delete temp;
			return false;
		}

		m_images.push_back(temp);
	}

	glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureId);

	glTexImage2D(Left, 0, GL_RGBA8, m_images[Left]->getWidth(), m_images[Left]->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_images[Left]->getPixels());
}
