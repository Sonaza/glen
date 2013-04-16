#ifndef GLEN_RENDERTEXTURE_HPP
#define GLEN_RENDERTEXTURE_HPP

#include <glen/opengl.hpp>
#include <glen/Config.hpp>
#include <glen/System/Vector2.hpp>

namespace glen
{

	class RenderTexture
	{
	public:
		RenderTexture();
		~RenderTexture();

		void create(uint32 width, uint32 height);

		void bind();
		void unbind();

	private:

		Vector2u	m_size;

		// GL handle to framebuffer object
		GLuint	m_fbo;
		// GL handle to renderbuffer object
		GLuint	m_rbo;

		// GL handle to framebuffer texture
		GLuint	m_texture;

		bool	m_created;

	};

}

#endif