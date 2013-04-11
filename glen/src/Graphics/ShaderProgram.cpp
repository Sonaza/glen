#include <glen/Graphics/ShaderProgram.hpp>
#include <glen/Graphics/Shader.hpp>
#include <glen/System/ErrorStream.hpp>

#include <glm/gtc/type_ptr.hpp>

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
void ShaderProgram::use() const
{
	glUseProgram(m_program);
}

//////////////////////////////////////////////////////////
void ShaderProgram::unUse() const
{
	assert(isInUse());
	glUseProgram(0);
}

//////////////////////////////////////////////////////////
bool ShaderProgram::isInUse() const
{
	GLint currentProgram = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
	return (currentProgram == (GLint)m_program);
}

//////////////////////////////////////////////////////////
GLint ShaderProgram::attrib(const GLchar* attribName) const
{
	return glGetAttribLocation(m_program, attribName);
}

//////////////////////////////////////////////////////////
GLuint ShaderProgram::uniform(const GLchar* uniformName) const
{
	return glGetUniformLocation(m_program, uniformName);
}

#define _GLEN_SHADERPROGRAM_SETTER_IMPL(GL_TYPE, TYPE_PREFIX, TYPE_SUFFIX) \
	void ShaderProgram::setAttrib(const GLchar* name, GL_TYPE v0) \
		{ assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 1 ## TYPE_SUFFIX (attrib(name), v0); } \
	void ShaderProgram::setAttrib(const GLchar* name, GL_TYPE v0, GL_TYPE v1) \
		{ assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 2 ## TYPE_SUFFIX (attrib(name), v0, v1); } \
	void ShaderProgram::setAttrib(const GLchar* name, GL_TYPE v0, GL_TYPE v1, GL_TYPE v2) \
		{ assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 3 ## TYPE_SUFFIX (attrib(name), v0, v1, v2); } \
	void ShaderProgram::setAttrib(const GLchar* name, GL_TYPE v0, GL_TYPE v1, GL_TYPE v2, GL_TYPE v3) \
		{ assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 4 ## TYPE_SUFFIX (attrib(name), v0, v1, v2, v3); } \
\
	void ShaderProgram::setAttrib1v(const GLchar* name, const GL_TYPE* v) \
		{ assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 1 ## TYPE_SUFFIX ## v (attrib(name), v); } \
	void ShaderProgram::setAttrib2v(const GLchar* name, const GL_TYPE* v) \
		{ assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 2 ## TYPE_SUFFIX ## v (attrib(name), v); } \
	void ShaderProgram::setAttrib3v(const GLchar* name, const GL_TYPE* v) \
		{ assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 3 ## TYPE_SUFFIX ## v (attrib(name), v); } \
	void ShaderProgram::setAttrib4v(const GLchar* name, const GL_TYPE* v) \
		{ assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 4 ## TYPE_SUFFIX ## v (attrib(name), v); } \
\
	void ShaderProgram::setUniform(const GLchar* name, GL_TYPE v0) \
		{ assert(isInUse()); glUniform1 ## TYPE_SUFFIX (uniform(name), v0); } \
	void ShaderProgram::setUniform(const GLchar* name, GL_TYPE v0, GL_TYPE v1) \
		{ assert(isInUse()); glUniform2 ## TYPE_SUFFIX (uniform(name), v0, v1); } \
	void ShaderProgram::setUniform(const GLchar* name, GL_TYPE v0, GL_TYPE v1, GL_TYPE v2) \
		{ assert(isInUse()); glUniform3 ## TYPE_SUFFIX (uniform(name), v0, v1, v2); } \
	void ShaderProgram::setUniform(const GLchar* name, GL_TYPE v0, GL_TYPE v1, GL_TYPE v2, GL_TYPE v3) \
		{ assert(isInUse()); glUniform4 ## TYPE_SUFFIX (uniform(name), v0, v1, v2, v3); } \
\
	void ShaderProgram::setUniform1v(const GLchar* name, const GL_TYPE* v, GLsizei count) \
		{ assert(isInUse()); glUniform1 ## TYPE_SUFFIX ## v (uniform(name), count, v); } \
	void ShaderProgram::setUniform2v(const GLchar* name, const GL_TYPE* v, GLsizei count) \
		{ assert(isInUse()); glUniform2 ## TYPE_SUFFIX ## v (uniform(name), count, v); } \
	void ShaderProgram::setUniform3v(const GLchar* name, const GL_TYPE* v, GLsizei count) \
		{ assert(isInUse()); glUniform3 ## TYPE_SUFFIX ## v (uniform(name), count, v); } \
	void ShaderProgram::setUniform4v(const GLchar* name, const GL_TYPE* v, GLsizei count) \
		{ assert(isInUse()); glUniform4 ## TYPE_SUFFIX ## v (uniform(name), count, v); } \

	_GLEN_SHADERPROGRAM_SETTER_IMPL(GLfloat, , f)
	_GLEN_SHADERPROGRAM_SETTER_IMPL(GLdouble, , d)
	_GLEN_SHADERPROGRAM_SETTER_IMPL(GLint, I, i)
	_GLEN_SHADERPROGRAM_SETTER_IMPL(GLuint, I, ui)

//////////////////////////////////////////////////////////
void ShaderProgram::setUniformMatrix2v(const GLchar* name, const GLfloat* v, GLsizei count, GLboolean transpose)
{
	assert(isInUse());
	glUniformMatrix2fv(uniform(name), count, transpose, v);
}

//////////////////////////////////////////////////////////
void ShaderProgram::setUniformMatrix3v(const GLchar* name, const GLfloat* v, GLsizei count, GLboolean transpose)
{
	assert(isInUse());
	glUniformMatrix3fv(uniform(name), count, transpose, v);
}

//////////////////////////////////////////////////////////
void ShaderProgram::setUniformMatrix4v(const GLchar* name, const GLfloat* v, GLsizei count, GLboolean transpose)
{
	assert(isInUse());
	glUniformMatrix4fv(uniform(name), count, transpose, v);
}

//////////////////////////////////////////////////////////
void ShaderProgram::setUniform(const GLchar* name, glm::mat2& m, GLboolean transpose)
{
	assert(isInUse());
	glUniformMatrix2fv(uniform(name), 1, transpose, glm::value_ptr(m));
}

//////////////////////////////////////////////////////////
void ShaderProgram::setUniform(const GLchar* name, glm::mat3& m, GLboolean transpose)
{
	assert(isInUse());
	glUniformMatrix3fv(uniform(name), 1, transpose, glm::value_ptr(m));
}

//////////////////////////////////////////////////////////
void ShaderProgram::setUniform(const GLchar* name, glm::mat4& m, GLboolean transpose)
{
	assert(isInUse());
	glUniformMatrix4fv(uniform(name), 1, transpose, glm::value_ptr(m));
}

//////////////////////////////////////////////////////////
bool ShaderProgram::compile(ShaderList &shaders)
{
	assert(!shaders.empty() && "Shaderlist can't be empty");

	// Attach all shaders
	for(ShaderList::iterator it = shaders.begin();
		it != shaders.end(); ++it)
	{
		(glAttachShader(m_program, (*it)->m_shader));
	}

	glBindFragDataLocation(m_program, 0, "finalColor");

	// Link attached shaders to the program
	glCheck(glLinkProgram(m_program));
	
	// Now we can detach shaders
	for(ShaderList::iterator it = shaders.begin();
		it != shaders.end(); ++it)
	{
		glCheck(glDetachShader(m_program, (*it)->m_shader));
	}

	// Check if program linking was successful
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

		err << "Shader program linking failed" << ErrorStream::error;
		return false;
	}

	return true;
}

}