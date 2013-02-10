#include <glen/Graphics/ShaderProgram.hpp>
#include <glen/Graphics/Shader.hpp>

#include <iostream>
#include <cassert>
#include <algorithm>

namespace glen
{

//////////////////////////////////////////////////////////
ShaderProgram::ShaderProgram() :
	m_program(0)
{
	m_program = glCreateProgram();
	glUseProgram(m_program);
}

//////////////////////////////////////////////////////////
ShaderProgram::~ShaderProgram()
{
	if(m_program != 0)
		glDeleteProgram(m_program);
}

//////////////////////////////////////////////////////////
void ShaderProgram::link(ShaderList &shaders)
{
	assert(shaders.empty() != NULL && "Shaderlist can't be empty");

	for(ShaderList::iterator it = shaders.begin();
		it != shaders.end(); ++it)
	{
		glAttachShader(m_program, (*it)->m_shader);
		//m_shaders.push_back(*it);
	}

	glBindFragDataLocation(m_program, 0, "finalColor");

	glLinkProgram(m_program);

	GLint status;
	glGetProgramiv(m_program, GL_LINK_STATUS, &status);

	if(status == GL_FALSE)
	{
		GLint infoLen;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLen);

		char *infoLog = new char[infoLen+1];
		glGetProgramInfoLog(m_program, infoLen, NULL, infoLog);

		std::cout << "Program linking error: " << infoLog;

		delete[] infoLog;
		infoLog = NULL;

		glDeleteProgram(m_program);
		m_program = 0;

		throw std::runtime_error("Shader program linking failed");
	}
}

}