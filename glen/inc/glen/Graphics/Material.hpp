#ifndef GLEN_MATERIAL_HPP
#define GLEN_MATERIAL_HPP

#include <glen/Graphics/Texture2D.hpp>
#include <glen/Graphics/Color.hpp>
#include <glen/Graphics/TextureTransform.hpp>

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
	typedef std::map<Texture2D::TextureType, TextureTransform> TextureTrans;

	class Material
	{
		friend class Model;
		friend class MaterialFactory;

	public:
		Material(void);
		virtual ~Material(void);

		void setTexture(Texture2D& texture) { m_textures[Texture2D::Diffuse] = &texture; m_transforms[Texture2D::Diffuse] = TextureTransform(); }

		template<Texture2D::TextureType type>
		void setTexture(Texture2D& texture) { m_textures[type] = &texture; m_transforms[type] = TextureTransform(); }
		
		template<Texture2D::TextureType type>
		TextureTransform* getTransform()
		{
			return m_transforms.find(type) != m_transforms.end()
				? &m_transforms[type]
				: NULL;
		}

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
		TextureTrans	m_transforms;

	};

}

#endif