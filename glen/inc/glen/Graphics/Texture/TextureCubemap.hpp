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
		
		bool _loadImages();
		void _freeImages();

		std::vector<std::string> m_filenames;

		std::vector<Image*>	m_images;

	};
	
}

#endif GLEN_TEXTURECUBEMAP_HPP
