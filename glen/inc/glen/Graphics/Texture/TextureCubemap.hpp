#ifndef GLEN_TEXTURECUBEMAP_HPP
#define GLEN_TEXTURECUBEMAP_HPP

#include <glen/Graphics/Texture/Texture.hpp>
#include <vector>

namespace glen
{
	
	class TextureCubemap : public Texture
	{
	public:
		TextureCubemap();
		~TextureCubemap();

		void TextureCubemap::bind() const;

		bool loadFromFile(const std::string& left,
						  const std::string& right,
						  const std::string& top,
						  const std::string& bottom,
						  const std::string& front,
						  const std::string& back);

	private:

		enum Surface
		{
			Left	= GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			Right	= GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			Top		= GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
			Bottom	= GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
			Front	= GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
			Back	= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
		};

		std::vector<Image*>	m_images;

	};
	
}

#endif GLEN_TEXTURECUBEMAP_HPP
