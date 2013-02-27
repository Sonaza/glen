#ifndef GLEN_MATERIAL_HPP
#define GLEN_MATERIAL_HPP

#include <glen/Graphics/ShaderProgram.hpp>
#include <glen/Graphics/Shader.hpp>

#include <map>
#include <string>

namespace glen
{

	class Texture;

	class Material
	{
		friend class Model;

	public:
		Material(void);
		virtual ~Material(void);

		void bind() const;
		void unbind() const;

		enum TextureType
		{
			Diffuse		= 0,	// Base image
			Normal		= 1,	// Normal Map
			Specular	= 2,	// Specular Map
			//ShadowMap	= 4,	// Shadow Map
		};

		void setTexture(TextureType type, Texture& texture);

	protected:

		virtual void foobar() =0;

		bool _loadshaders(const std::string& vertex, const std::string& fragment);

		void _linkVertexAttrib();
		virtual void _bindTextures();

		ShaderProgram*	m_program;
		ShaderList		m_shaders;

		std::map<TextureType, Texture*> m_textures;

	};

}

#endif