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

		void use() const;
		bool isInUse() const;

		bool compile(ShaderList &shaders);

		GLint attrib(const GLchar* attribName) const;
		GLuint uniform(const GLchar* uniformName) const;

		#define _GLEN_SHADERPROGRAM_SETTER(GL_TYPE) \
			void setAttrib(const GLchar* attribName, GL_TYPE v0); \
			void setAttrib(const GLchar* attribName, GL_TYPE v0, GL_TYPE v1); \
			void setAttrib(const GLchar* attribName, GL_TYPE v0, GL_TYPE v1, GL_TYPE v2); \
			void setAttrib(const GLchar* attribName, GL_TYPE v0, GL_TYPE v1, GL_TYPE v2, GL_TYPE v3); \
\
			void setAttrib1v(const GLchar* attribName, const GL_TYPE* v); \
			void setAttrib2v(const GLchar* attribName, const GL_TYPE* v); \
			void setAttrib3v(const GLchar* attribName, const GL_TYPE* v); \
			void setAttrib4v(const GLchar* attribName, const GL_TYPE* v); \
\
			void setUniform(const GLchar* uniformName, GL_TYPE v0); \
			void setUniform(const GLchar* uniformName, GL_TYPE v0, GL_TYPE v1); \
			void setUniform(const GLchar* uniformName, GL_TYPE v0, GL_TYPE v1, GL_TYPE v2); \
			void setUniform(const GLchar* uniformName, GL_TYPE v0, GL_TYPE v1, GL_TYPE v2, GL_TYPE v3); \
\
			void setUniform1v(const GLchar* uniformName, const GL_TYPE* v, GLsizei count=1); \
			void setUniform2v(const GLchar* uniformName, const GL_TYPE* v, GLsizei count=1); \
			void setUniform3v(const GLchar* uniformName, const GL_TYPE* v, GLsizei count=1); \
			void setUniform4v(const GLchar* uniformName, const GL_TYPE* v, GLsizei count=1); \

		_GLEN_SHADERPROGRAM_SETTER(GLfloat)
		//_GLEN_SHADERPROGRAM_UNIFORM_SETTER(GLdouble)
		//_GLEN_SHADERPROGRAM_UNIFORM_SETTER(GLint)
		//_GLEN_SHADERPROGRAM_UNIFORM_SETTER(GLuint)

	private:

		GLuint		m_program;

		// Store a list of program's shaders
		ShaderList	m_shaders;
	};

}

#endif
