#ifndef GLEN_MATERIAL_HPP
#define GLEN_MATERIAL_HPP

#include <glen/Graphics/Color.hpp>
#include <glen/Graphics/Texture/Texture2D.hpp>
#include <glen/Graphics/Texture/TextureCubemap.hpp>
#include <glen/Graphics/Texture/TextureTransform.hpp>

#include <glen/System/Types.hpp>

#include <map>
#include <vector>
#include <string>

namespace glen
{

	class Shader;
	class ShaderProgram;
	class ShaderAsset;

	typedef std::map<Texture::Type, Texture*> TextureList;
	typedef std::map<Texture::Type, TextureTransform> TextureTrans;

	typedef std::vector<std::string> ShaderDefines;

	class Material
	{
		friend class Model;
		friend class MaterialFactory;

	public:
		Material(void);
		virtual ~Material(void);

		void setTexture(Texture::Type type, Texture* texture);

		/*template<Texture::Type type>
		void setTexture(Texture* texture) { m_textures[type] = texture; m_transforms[type] = TextureTransform(); }
		*/

		TextureTransform* getTransform(Texture::Type type)
		{
			TextureTransform* temp = m_transforms.find(type) != m_transforms.end()
				? &m_transforms[type]
				: NULL;

			assert(temp);

			return temp;
		}

		struct Matrices
		{
			mat4 projection;
			mat4 view;
			mat4 model;
		};

		enum Type
		{
			Diffuse,
			SpecularDiffuse,
			Skybox
		};

		void setMatrices(Matrices& matrices);

		void bind();
		void unbind() const;

		void setColor(Color c);
		void setColor(uint8 r, uint8 g, uint8 b, uint8 a = 255);

		void setOpacity(uint8 a);

	protected:

		bool _loadshaders(const std::string& vertex, const std::string& fragment, ShaderDefines defines = ShaderDefines());

		void _linkVertexAttrib();
		virtual void _bindTextures();

		ShaderAsset*	m_shaderAsset;

		TextureList		m_textures;
		TextureTrans	m_transforms;

		Color			m_color;

	};

}

#endif