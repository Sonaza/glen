#ifndef SHADER_HPP
#define SHADER_HPP

#include <glen/ogl.h>

#include <string>

namespace glen
{

	class ShaderProgram;

	class Shader
	{
		friend class ShaderProgram;

	public:
		enum Type
		{
			Vertex,
			Fragment
		};

		Shader(void);
		Shader(const std::string &path, Type type);

		~Shader(void);

		bool loadFromFile(const std::string &path, Type type);
	
		inline Type getType() const { return m_type; }

	private:

		GLuint			m_shader;
		// Shader's parent program
		ShaderProgram*	m_program;
		// Type of the shader
		Type			m_type;
	};

}

#endif
