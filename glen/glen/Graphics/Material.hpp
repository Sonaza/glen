#ifndef GLEN_MATERIAL_HPP
#define GLEN_MATERIAL_HPP

#include <glen/Graphics/Texture2D.hpp>
#include <glen/Graphics/Color.hpp>

#include <glm/glm.hpp>

#include <map>
#include <vector>
#include <string>

namespace glen
{

	class ShaderProgram;
	class Shader;

	typedef std::vector<Shader*> ShaderList;
	typedef std::map<Texture2D::TextureType, Texture2D*> TextureList;

	class Material
	{
		friend class Model;
		friend class MaterialFactory;

	public:
		Material(void);
		virtual ~Material(void);

		void setTexture(Texture2D& texture) { m_textures[Texture2D::Diffuse] = &texture; }

		template<Texture2D::TextureType type>
		void setTexture(Texture2D& texture) { m_textures[type] = &texture; }

		void updateMatrix(glm::mat4& modelMatrix);

		void bind() const;
		void unbind() const;

	protected:

		bool _loadshaders(const std::string& vertex, const std::string& fragment);

		void _linkVertexAttrib();
		virtual void _bindTextures();

		ShaderProgram*	m_program;
		ShaderList		m_shaders;
		TextureList		m_textures;

	};

}

#endif