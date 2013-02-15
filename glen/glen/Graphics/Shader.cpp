#include <glen/Graphics/Shader.hpp>

#include <iostream>
#include <sstream>
#include <fstream>

namespace glen
{

///////////////////////////////////////////////////////
Shader::Shader(void) :
	m_shader(0)
{
}

///////////////////////////////////////////////////////
Shader::Shader(const std::string &path, Type type) :
	m_shader(0)
{
	loadFromFile(path, type);
}

///////////////////////////////////////////////////////
Shader::~Shader(void)
{
	if(m_shader != NULL)
		glDeleteShader(m_shader);
}

///////////////////////////////////////////////////////
bool Shader::loadFromFile(const std::string &path, Type type)
{
	std::ifstream file(path);

	if(!file.is_open())
	{
		throw std::runtime_error("Unable to open shader file: " + path);
		return false;
	}

	std::stringstream filebuffer;
	filebuffer << file.rdbuf();
	file.close();

	std::string code = filebuffer.str();

	m_filename = path;

	return compile(code.c_str(), type == Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER));
}

///////////////////////////////////////////////////////
bool Shader::loadFromMemory(const char* data, Type type)
{
	m_filename = "Shader";
	return compile(data, type == Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER));
}

///////////////////////////////////////////////////////
bool Shader::compile(const char* code, GLenum type)
{
	// Create new shader and upload the code
	m_shader = glCreateShader(type == Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
	if(m_shader == 0)
	{
		throw std::runtime_error("glCreateShader failed");
		return false;
	}

	glShaderSource(m_shader, 1, &code, NULL);

	// Attempt to compile the shader
	glCompileShader(m_shader);

	// Retrieve shader status
	GLint status;
	glGetShaderiv(m_shader, GL_COMPILE_STATUS, &status); 

	if(status == GL_FALSE)
	{
		glDeleteShader(m_shader);
		m_shader = 0;

		std::cout << m_filename << " compilation failed" << std::endl;
		m_filename = "";
	}

	// Output compilation log
	GLint infoLen = 0;
	glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &infoLen);

	if(infoLen > 1)
	{
		char *infoLog = new char[infoLen+1];
		glGetShaderInfoLog(m_shader, infoLen, NULL, infoLog);

		// Output compilation log into console
		std::cout << infoLog << std::endl;

		delete[] infoLog;
		infoLog = NULL;
	}

	if(status == GL_FALSE) return false;

	return true;
}

}