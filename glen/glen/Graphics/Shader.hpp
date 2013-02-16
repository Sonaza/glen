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
		bool loadFromMemory(const char* data, Type type);
	
		inline Type getType() const { return m_type; }

		inline bool isValid() const { return m_valid; }

	protected:

		GLuint			m_shader;
		std::string		m_filename;

		// Type of the shader
		Type			m_type;

	private:

		bool			m_valid;

		bool compile(const char* code, GLenum type);

	};

}

#endif
