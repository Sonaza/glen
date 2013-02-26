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

		enum TextureType
		{
			Diffuse,	// Base image
			Normal,		// Normal Map
			Specular,	// Specular Map
		};

		void setTexture(TextureType type, const Texture& texture);

	protected:

		bool _loadshaders(const std::string& vertex, const std::string& fragment);

		void _linkVertexAttrib();

		ShaderProgram*	m_program;
		ShaderList		m_shaders;

		std::map<TextureType, Texture*> m_textures;

	};

}

#endif