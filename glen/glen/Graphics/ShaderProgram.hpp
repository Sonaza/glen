#ifndef GLEN_SHADERPROGRAM_HPP
#define GLEN_SHADERPROGRAM_HPP

#include <glen/ogl.h>

#include <vector>

namespace glen
{
	class Shader;

	typedef std::vector<Shader*> ShaderList;

	class ShaderProgram
	{
	public:
		ShaderProgram(void);
		~ShaderProgram(void);

		void link(ShaderList &shaders);

	private:

		GLuint		m_program;

		// Store a list of program's shaders
		ShaderList	m_shaders;
	};

}

#endif
