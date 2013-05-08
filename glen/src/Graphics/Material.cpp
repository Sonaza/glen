#include <glen/Graphics/Material.hpp>

#include <glen/Graphics/ShaderManager.hpp>

#include <glen/Graphics/Shader.hpp>
#include <glen/Graphics/ShaderProgram.hpp>
#include <glen/Graphics/ShaderAsset.hpp>

#include <glen/Graphics/Camera.hpp>

#define setAttribPointer(NAME, SIZE, STRIDE, OFFSET) \
	do { glEnableVertexAttribArray(m_shaderAsset->program->attrib(NAME)); \
	glCheck(glVertexAttribPointer( \
		m_shaderAsset->program->attrib(NAME), SIZE, GL_FLOAT, GL_FALSE, \
		sizeof(GLfloat) * STRIDE, (void*)(sizeof(GLfloat) * OFFSET) \
	)); } while(0) \

namespace
{
	sf::Clock timer;
}

namespace glen
{

///////////////////////////////////////////////////
Material::Material(void)
{
}

///////////////////////////////////////////////////
Material::~Material(void)
{
	
}

///////////////////////////////////////////////////
void Material::bind()
{
	assert(m_shaderAsset->program != NULL && "Program must be initialized");
	m_shaderAsset->program->use();

	_bindTextures();
}

///////////////////////////////////////////////////
void Material::unbind() const
{
	assert(m_shaderAsset->program != NULL && "Program must be initialized");
	m_shaderAsset->program->unUse();
}

///////////////////////////////////////////////////
void Material::setMatrices(Matrices& matrices)
{
	m_shaderAsset->program->setUniform("u_matrix.model", matrices.model);
	m_shaderAsset->program->setUniform("u_matrix.view", matrices.view);
	m_shaderAsset->program->setUniform("u_matrix.proj", matrices.projection);

	m_shaderAsset->program->setUniform("u_time", timer.getElapsedTime().asSeconds());
}

///////////////////////////////////////////////////
bool Material::_loadshaders(const std::string& vertex, const std::string& fragment, ShaderDefines defines)
{
	// Load shaders
	m_shaderAsset = ShaderManager::loadShader(vertex, fragment, defines);

	m_shaderAsset->program->use();

	// Set texturing uniforms
	m_shaderAsset->program->setUniform("u_texture.diffuse",	Texture2D::Diffuse);
	m_shaderAsset->program->setUniform("u_texture.normal",	Texture2D::Normal);
	m_shaderAsset->program->setUniform("u_texture.specular", Texture2D::Specular);

	m_shaderAsset->program->unUse();

	return true;
}

///////////////////////////////////////////////////
void Material::_linkVertexAttrib()
{
	setAttribPointer("a_position", 3, 9, 0);
	setAttribPointer("a_texcoord", 3, 9, 3);
	setAttribPointer("a_normal", 3, 9, 6);
}

///////////////////////////////////////////////////
void Material::_bindTextures()
{
	for(TextureList::iterator it = m_textures.begin();
		it != m_textures.end(); ++it)
	{
		glActiveTexture(GL_TEXTURE0 + it->first);
		it->second->bind();
	}
	
	if(m_transforms.find(Texture2D::Diffuse) != m_transforms.end())
		m_shaderAsset->program->setUniform("u_texmatrix.diffuse", m_transforms[Texture2D::Diffuse].getMatrix());

	if(m_transforms.find(Texture2D::Normal) != m_transforms.end())
		m_shaderAsset->program->setUniform("u_texmatrix.normalmap", m_transforms[Texture2D::Normal].getMatrix());
	
	if(m_transforms.find(Texture2D::Specular) != m_transforms.end())
		m_shaderAsset->program->setUniform("u_texmatrix.specular", m_transforms[Texture2D::Specular].getMatrix());
}

}