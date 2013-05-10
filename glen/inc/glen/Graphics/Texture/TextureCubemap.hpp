#ifndef GLEN_TEXTURECUBEMAP_HPP
#define GLEN_TEXTURECUBEMAP_HPP

#include <glen/Graphics/Texture/Texture.hpp>
#include <vector>

namespace glen
{
	
	class TextureCubemap : public Texture
	{
	public:
		TextureCubemap(void);
		virtual ~TextureCubemap(void);

		void bind() const;

		bool loadFromFile(const std::string& left,
						  const std::string& right,
						  const std::string& top,
						  const std::string& bottom,
						  const std::string& front,
						  const std::string& back);

		vec2i getSize() const { assert(m_images[0]); return m_images[0]->getSize(); }

	private:
		
		bool _loadImages();
		void _freeImages();

		std::vector<std::string> m_filenames;

		std::vector<Image*>	m_images;

	};
	
}

#endif GLEN_TEXTURECUBEMAP_HPP
