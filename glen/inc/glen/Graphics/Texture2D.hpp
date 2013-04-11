#ifndef GLEN_TEXTURE_HPP
#define GLEN_TEXTURE_HPP

#include <glen/opengl.hpp>
#include <glen/Config.hpp>
#include <glen/Graphics/stb_image/stb_image.h>

#include <string>

namespace glen
{

	class Texture2D
	{
	public:
		Texture2D(void);
		virtual ~Texture2D(void);

		enum TextureType
		{
			Diffuse		= 0,	// Base image
			Normal		= 1,	// Normal Map
			Specular	= 2,	// Specular Map
			//ShadowMap	= 4,	// Shadow Map
		};

		struct Settings
		{
			Settings()
			{
				clamping = Repeat;
				filtering = Linear;
			}

			enum Clamping
			{
				Clamp,
				Repeat
			};

			enum Filtering
			{
				Linear,
				Nearest
			};

			Clamping clamping;
			Filtering filtering;
		};

		void bind() const;

		bool loadFromFile(const std::string& path);

		void setClamping(const Settings::Clamping value);
		void setFiltering(const Settings::Filtering value);

		//void setAnisotropy(const float )

	private:

		GLuint	m_texture;

		Settings m_settings;

	};

}

#endif
