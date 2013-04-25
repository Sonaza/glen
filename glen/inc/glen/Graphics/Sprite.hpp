#ifndef GLEN_SPRITE_HPP
#define GLEN_SPRITE_HPP

#include <glen/opengl.hpp>
#include <glen/System/Types.hpp>

#include <string>
#include <vector>
#include <cassert>
#include <memory>

namespace glen
{
	
	class Texture2D;

	class Shader;
	class ShaderProgram;

	typedef std::unique_ptr<ShaderProgram> ShaderProgramPtr;

	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void setTexture2D(Texture2D* texture);

		void render(mat4 &transform);

	private:

		bool _loadshaders(const std::string& vertex, const std::string& fragment);
		void _generateObjects();

		Texture2D*	m_texture;

		GLuint	m_vbo;
		GLuint	m_vao;

		std::vector<GLfloat>	m_data;

		// A shader program used for all sprite rendering
		static ShaderProgramPtr		m_program;
		static std::vector<Shader*>	m_shaders;

	};
	
}

#endif GLEN_SPRITE_HPP
