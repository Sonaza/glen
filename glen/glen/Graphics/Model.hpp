#ifndef GLEN_MODEL_HPP
#define GLEN_MODEL_HPP

#include <glen/Graphics/MeshLoader.hpp>
#include <glen/ogl.h>

#include <glen/Graphics/ShaderProgram.hpp>
#include <glen/Graphics/Shader.hpp>

#include <vector>
#include <string>
#include <cassert>

namespace glen
{

class Model
{
public:
	Model(void);
	~Model(void);

	bool loadFromFile(const std::string& path);

protected:

	ShaderProgram*			m_program;
	std::vector<Shader*>	m_shaders;

	GLuint		m_vbo;
	GLuint		m_vao;

	MeshData*	m_meshdata;

};

}

#endif