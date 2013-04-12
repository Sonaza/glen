#include <glen/Graphics/RenderTexture.hpp>

namespace glen
{

///////////////////////////////////////////////////////////
RenderTexture::RenderTexture() :
	m_fbo(0),
	m_rbo(0),
	m_texture(0),
	m_created(false)
{
	
}

///////////////////////////////////////////////////////////
RenderTexture::~RenderTexture()
{
	if(m_created)
	{
		glDeleteFramebuffers(1, &m_fbo);
		glDeleteRenderbuffers(1, &m_rbo);
		glDeleteTextures(1, &m_texture);
	}
}

///////////////////////////////////////////////////////////
void RenderTexture::create(uint32 width, uint32 height)
{
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

	glGenRenderbuffers(1, &m_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	m_created = true;
}

///////////////////////////////////////////////////////////
void RenderTexture::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

///////////////////////////////////////////////////////////
void RenderTexture::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

}