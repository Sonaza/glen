#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <glen/ogl.h>

#include <vector>

namespace glen
{

	class Shader;

	class ShaderProgram
	{
	public:
		ShaderProgram(void);
		~ShaderProgram(void);

		void addShader(Shader &shader);

	private:

		GLuint		m_program;

		std::vector<Shader*>	m_shaders;
	};

}

#endif
