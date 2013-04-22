#ifndef GLEN_TEXTUREBASE_HPP
#define GLEN_TEXTUREBASE_HPP

#include <glen/opengl.hpp>
#include <glen/Config.hpp>
#include <glen/System/Vector2.hpp>
#include <glen/System/ErrorStream.hpp>

#include <string>

#include <glen/Graphics/Image.hpp>

namespace glen
{
	
	class Texture
	{
	public:
		Texture();
		virtual ~Texture();

		enum TextureType
		{
			Diffuse		= 0,	// Base image
			Normal		= 1,	// Normal Map
			Specular	= 2,	// Specular Map
		};

		enum Clamping
		{
			Clamp,	// Clamp texture to its dimensions
			Repeat	// Repeat texture over
		};

		enum Filtering
		{
			Linear,	// Linear mipmapped filter
			Nearest	// Nearest pixelated filter
		};

		struct Settings
		{
			Settings()
			{
				clamping	= Repeat;
				filtering	= Linear;
				anisotropy	= 16;
			}

			Clamping	clamping;
			Filtering	filtering;
			uint32		anisotropy;
		};

		virtual void bind() const =0;

		virtual void setClamping(const Clamping value);
		virtual void setFiltering(const Filtering value);

		virtual void setAnisotropy(const uint32 value);

		virtual Vector2i getSize() const { return Vector2i(); }

	protected:

		GLuint		m_textureId;

		Settings	m_settings;
		bool		m_loaded;

	};
	
}

#endif GLEN_TEXTUREBASE_HPP