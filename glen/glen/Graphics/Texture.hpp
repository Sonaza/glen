#ifndef GLEN_TEXTURE_HPP
#define GLEN_TEXTURE_HPP

#include <glen/ogl.h>
#include <glen/Config.hpp>
#include <glen/Graphics/stb_image/stb_image.h>

#include <string>

namespace glen
{

	class Texture
	{
	public:
		Texture(void);
		virtual ~Texture(void);

		void bind() const;

		bool loadFromFile(const std::string& path, const bool clamp = true);

	private:

		GLuint	m_texture;

	};

}

#endif
