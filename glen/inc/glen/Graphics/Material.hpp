#ifndef GLEN_MATERIAL_HPP
#define GLEN_MATERIAL_HPP

#include <glen/Graphics/Texture/Texture2D.hpp>
#include <glen/Graphics/Texture/TextureTransform.hpp>

#include <glm/glm.hpp>

#include <map>
#include <vector>
#include <string>

namespace glen
{

	class Shader;
	class ShaderProgram;
	class ShaderAsset;

	typedef std::map<Texture2D::TextureType, Texture2D*> TextureList;
	typedef std::map<Texture2D::TextureType, TextureTransform> TextureTrans;

	typedef std::vector<std::string> ShaderDefines;

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

		struct Matrices
		{
			glm::mat4 projection;
			glm::mat4 view;
			glm::mat4 model;
		};

		void setMatrices(Matrices& matrices);

		void bind();
		void unbind() const;

		sf::Clock timer;

	protected:

		bool _loadshaders(const std::string& vertex, const std::string& fragment, ShaderDefines defines = ShaderDefines());

		void _linkVertexAttrib();
		virtual void _bindTextures();

		ShaderAsset*	m_shaderAsset;

		TextureList		m_textures;
		TextureTrans	m_transforms;

	};

}

#endif