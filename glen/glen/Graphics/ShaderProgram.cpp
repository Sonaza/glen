#include <glen/Graphics/ShaderProgram.hpp>
#include <glen/Graphics/Shader.hpp>

namespace glen
{

ShaderProgram::ShaderProgram()
{
	m_program = glCreateProgram();

	glBindFragDataLocation(m_program, 0, "outcolor");

	glLinkProgram(m_program);
	glUseProgram(m_program);
}

ShaderProgram::~ShaderProgram()
{
	
}

void ShaderProgram::addShader(Shader &shader)
{
	glAttachShader(m_program, shader.m_shader);

	m_shaders.push_back(&shader);
}

}