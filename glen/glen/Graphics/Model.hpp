#ifndef GLEN_MODEL_HPP
#define GLEN_MODEL_HPP

#include <glen/Graphics/MeshLoader.hpp>
#include <glen/ogl.h>

#include <glen/Graphics/ShaderProgram.hpp>
#include <glen/Graphics/Shader.hpp>
#include <glen/System/Transformable.hpp>

#include <vector>
#include <string>
#include <cassert>

namespace glen
{

	class Texture;

	class Model : public Transformable
	{
	public:
		Model(void);
		~Model(void);

		void setTexture(Texture& texture);

		bool loadFromFile(const std::string& path);

		void render();

	protected:

		ShaderProgram*	m_program;
		ShaderList		m_shaders;

		MeshData*	m_meshdata;
		Texture*	m_texture;

		GLuint		m_vbo;
		GLuint		m_vao;

	};

}

#endif