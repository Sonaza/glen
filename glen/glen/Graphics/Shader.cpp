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
Shader::~Shader(void)
{
	if(m_shader != NULL)
		glDeleteShader(m_shader);
}

///////////////////////////////////////////////////////
bool Shader::loadFromFile(const std::string &path, Type type)
{
	std::ifstream file(path);

	if(!file.good())
	{
		throw std::runtime_error("Unable to open shader file: " + path);

		return false;
	}

	std::stringstream filebuffer;
	filebuffer << file.rdbuf();
	file.close();

	std::string code = filebuffer.str();
	const char* shaderCode = code.c_str();

	// Create new shader and upload the code
	m_shader = glCreateShader(type == Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
	glShaderSource(m_shader, 1, &shaderCode, NULL);

	// Attempt to compile the shader
	glCompileShader(m_shader);

	// Retrieve shader status
	GLint status;
	glGetShaderiv(m_shader, GL_COMPILE_STATUS, &status); 

	if(status == GL_FALSE)
	{
		glDeleteShader(m_shader);

		std::cout << "Shader compilation failed (" << path << ")" << std::endl;
	}

	// Check up if everything went alright
	GLint infoLen = 0;
	glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &infoLen);

	if(infoLen > 1)
	{
		char *infoLog = new char[infoLen];
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