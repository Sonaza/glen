#include <glen/Graphics/Material.hpp>

#include <glen/Graphics/ShaderProgram.hpp>
#include <glen/Graphics/Shader.hpp>
#include <glen/Graphics/Camera.hpp>

#define ATTRIB_POINTER(NAME, SIZE, STRIDE, OFFSET) \
	do { glEnableVertexAttribArray(m_program->attrib(NAME)); \
	glCheck(glVertexAttribPointer( \
		m_program->attrib(NAME), SIZE, GL_FLOAT, GL_FALSE, \
		sizeof(GLfloat) * STRIDE, (void*)(sizeof(GLfloat) * OFFSET) \
	)); } while(0) \

namespace glen
{

///////////////////////////////////////////////////
Material::Material(void) :
	m_program(NULL)
{
}

///////////////////////////////////////////////////
Material::~Material(void)
{
	if(m_program != NULL)
	{
		delete m_program;
		m_program = NULL;
	}

	for(ShaderList::iterator it = m_shaders.begin();
		it != m_shaders.end(); ++it)
	{
		delete *it;
	}

	m_shaders.clear();
}

///////////////////////////////////////////////////
void Material::bind() const
{
	assert(m_program != NULL && "Program must be initialized");
	m_program->use();
}

///////////////////////////////////////////////////
void Material::unbind() const
{
	assert(m_program != NULL && "Program must be initialized");
	m_program->unUse();
}

///////////////////////////////////////////////////
void Material::updateMatrix(glm::mat4& model)
{
	Camera* camera = Camera::activeCamera();
	
	m_program->setUniform("u_model", model);
	m_program->setUniform("u_view", camera->getMatrix());
	m_program->setUniform("u_proj", camera->getProjectionMatrix());
}

///////////////////////////////////////////////////
bool Material::_loadshaders(const std::string& vertex, const std::string& fragment, ShaderDefines defines)
{
	// Create shaders
	Shader* vertexShader = new(std::nothrow) Shader(defines);
	vertexShader->loadFromFile(vertex, Shader::Vertex);

	//Shader* geometryShader = new(std::nothrow) Shader();
	//geometryShader->loadFromFile(geometry, Shader::Geometry);

	Shader* fragmentShader = new(std::nothrow) Shader(defines);
	fragmentShader->loadFromFile(fragment, Shader::Fragment);

	m_shaders.push_back(vertexShader);
	//m_shaders.push_back(geometryShader);
	m_shaders.push_back(fragmentShader);

	// Attempt to allocate and link shader program
	m_program = new(std::nothrow) ShaderProgram();
	if(!m_program->compile(m_shaders))
	{
		m_shaders.clear();

		delete vertexShader;
		delete fragmentShader;

		delete m_program;
		m_program = NULL;

		return false;
	}

	m_program->use();

	// Set texturing uniforms
	m_program->setUniform("u_texture.diffuse",	Texture2D::Diffuse);
	m_program->setUniform("u_texture.normal",	Texture2D::Normal);
	m_program->setUniform("u_texture.specular", Texture2D::Specular);

	m_program->unUse();

	return true;
}

///////////////////////////////////////////////////
void Material::_linkVertexAttrib()
{
	ATTRIB_POINTER("a_position", 3, 9, 0);
	ATTRIB_POINTER("a_texcoord", 3, 9, 3);
	ATTRIB_POINTER("a_normal", 3, 9, 6);
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
		m_program->setUniform("u_texmatrix.diffuse", m_transforms[Texture2D::Diffuse].getMatrix());

	if(m_transforms.find(Texture2D::Normal) != m_transforms.end())
		m_program->setUniform("u_texmatrix.normalmap", m_transforms[Texture2D::Normal].getMatrix());
	
	if(m_transforms.find(Texture2D::Specular) != m_transforms.end())
		m_program->setUniform("u_texmatrix.specular", m_transforms[Texture2D::Specular].getMatrix());
}

}